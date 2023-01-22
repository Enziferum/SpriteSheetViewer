#include <viewer/ViewerManager.hpp>
#include <viewer/AnimationIO.hpp>
#include <viewer/ISceneView.hpp>
#include <viewer/SpriteCutter.hpp>
#include <viewer/SpriteSheet.hpp>

#include <viewer/commands/AddFrameCommand.hpp>
#include <viewer/commands/DeleteFrameCommand.hpp>

namespace viewer {
    ViewerManager::ViewerManager(robot2D::MessageBus& messageBus,
                                 MessageDispatcher& messageDispatcher):
                                 m_messageBus{messageBus},
                                 m_messageDispatcher{messageDispatcher}
    {}


    void ViewerManager::setup(ISceneView* view) {
        m_view = view;
        m_messageDispatcher.onMessage<AddAnimationMessage>(MessageID::AddAnimation,
                                                           BIND_CLASS_FN(onAddAnimation));

        m_messageDispatcher.onMessage<SwitchAnimationMessage>(MessageID::SwitchAnimation,
                                                              BIND_CLASS_FN(onSwitchAnimation));


        m_messageDispatcher.onMessage<SaveAnimationsMessage>(MessageID::SaveAnimations,
                                                             BIND_CLASS_FN(onSaveAnimations));

        m_messageDispatcher.onMessage<DeleteAnimationMessage>(MessageID::DeleteAnimation,
                                                              BIND_CLASS_FN(onDeleteAnimation));

        m_messageDispatcher.onMessage<LoadImageMessage>(MessageID::LoadImage, BIND_CLASS_FN(onLoadImage));

        m_messageDispatcher.onMessage<LoadXmlMessage>(MessageID::LoadXml, BIND_CLASS_FN(onLoadXml));
    }


    void ViewerManager::onAddAnimation(const AddAnimationMessage& message) {
        ViewerAnimation viewerAnimation{};
        viewerAnimation.getAnimation().title = message.name;
        m_animations.emplace_back(std::move(viewerAnimation));
        m_currentAnimation = m_animations.size() - 1;

        auto animation = m_animations[m_currentAnimation].getAnimation();
        m_view -> updateAnimation(&m_animations[m_currentAnimation]);
    }

    void ViewerManager::onSaveAnimations(const SaveAnimationsMessage& message) {
        AnimationIO animationIo{};
        AnimationList animations;
        for(const auto& animation: m_animations)
            animations.emplace_back(animation.getAnimation());
        auto maskColor = m_view -> getImageMaskColor();
        if(!animationIo.saveToFile(message.filePath, "", maskColor, animations)) {
            RB_ERROR("Can't save animation");
        }
    }

    void ViewerManager::onDeleteAnimation(const DeleteAnimationMessage& message) {
        assert(message.deleteIndex < m_animations.size());
        if(m_animations.size() > 1)
            m_animations.erase(m_animations.begin() + message.deleteIndex);
        m_currentAnimation = message.switchToIndex;

        auto animation = m_animations[m_currentAnimation].getAnimation();
        m_view -> updateAnimation(&m_animations[m_currentAnimation]);
    }

    void ViewerManager::onSwitchAnimation(const SwitchAnimationMessage& message) {
        m_currentAnimation = message.indexTo;

        auto animation = m_animations[m_currentAnimation].getAnimation();
        m_view -> updateAnimation(&m_animations[m_currentAnimation]);
    }

    void ViewerManager::onLoadImage(const LoadImageMessage& message) {
        robot2D::Image image{};
        if(!image.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load image by path {0}", message.filePath);
            return;
        }

        m_view -> onLoadImage(std::move(image));
    }

    void ViewerManager::onLoadXml(const LoadXmlMessage& message) {
        m_currentAnimation = 0;
        m_animations.clear();

        SpriteSheet spriteSheet;
        if(!spriteSheet.loadFromFile(message.filePath)) {}
    }

    void ViewerManager::undo() {
        m_commandStack.undo();
    }

    void ViewerManager::redo() {
        m_commandStack.redo();
    }

    void ViewerManager::deleteFrame() {
        if(updateIndex != -1) {
            auto frame = m_animations[m_currentAnimation][updateIndex];
            m_animations[m_currentAnimation].eraseFrame(updateIndex);

            frame.borderColor = robot2D::Color::Green;
            m_commandStack.addCommand<DeleteFrameCommand>(
                    m_animations[m_currentAnimation],
                    frame,
                    updateIndex
            );

            updateIndex = -1;
            return;
        }
    }

    void ViewerManager::cutFrames(const robot2D::FloatRect& clipRegion,
                                  const robot2D::vec2f& worldPosition) {
        auto dd = viewer::Collider{};
        if(updateIndex == -1) {
            dd.setRect(clipRegion);
            if(dd.notZero() ) {
//                auto&& frames = SpriteCutter{}.cutFrames(
//                        {clipRegion.lx, clipRegion.ly, clipRegion.width, clipRegion.height},
//                        const_cast<robot2D::Texture &>(*m_animatedSprite.getTexture()),
//                        worldPosition
//                );

                std::vector<robot2D::IntRect> frames;

                frames.erase(
                        std::unique(frames.begin(), frames.end()),
                        frames.end());
                std::sort(frames.begin(), frames.end());

                for(const auto& frame: frames) {
                    dd.setRect({frame.lx, frame.ly, frame.width, frame.height});
                    m_commandStack.addCommand<AddFrameCommand>(m_animations[m_currentAnimation], dd);
                    m_animations[m_currentAnimation].addFrame(dd, worldPosition);
                }

                dd.setRect(clipRegion);
                m_commandStack.addCommand<AddFrameCommand>(m_animations[m_currentAnimation], dd);
                m_animations[m_currentAnimation].addFrame(dd, worldPosition);
            }
        } else {
            if(dd.notZero()) {
                m_animations[m_currentAnimation][updateIndex].setRect(clipRegion);
                m_animations[m_currentAnimation][updateIndex].showMovePoints = false;
            }
        }
    }

    std::pair<bool, int> ViewerManager::getCollisionPair(const robot2D::vec2f &point) {
        return m_animations[m_currentAnimation].contains(point);
    }

    void ViewerManager::setCollider(const robot2D::FloatRect& collidingRect) {
        if(updateIndex >= 0)
            m_animations[m_currentAnimation][updateIndex].setRect(collidingRect);
    }

    Collider& ViewerManager::getCollider(int index) {
        //assert(index < m_animations[m_currentAnimation].getSize());
        return m_animations[m_currentAnimation][index];
    }


} // namespace viewer