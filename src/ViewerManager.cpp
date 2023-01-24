#include <viewer/ViewerManager.hpp>
#include <viewer/AnimationIO.hpp>
#include <viewer/SpriteCutter.hpp>
#include <viewer/SpriteSheet.hpp>
#include <viewer/ISceneView.hpp>

#include <viewer/commands/AddFrameCommand.hpp>
#include <viewer/commands/DeleteFrameCommand.hpp>
#include <filesystem>

namespace viewer {

    namespace {
        constexpr int NO_INDEX = -1;
    }

    ViewerManager::ViewerManager(robot2D::MessageBus& messageBus,
                                 MessageDispatcher& messageDispatcher):
                                 m_messageBus{messageBus},
                                 m_messageDispatcher{messageDispatcher}
    {}


    void ViewerManager::setup(ISceneView* view) {
        //assert(m_view != nullptr && "View must be not nullptr");
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
        // TODO(a.raag): Get Texture Path
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
        m_currentAnimation = NO_INDEX;
        m_updateIndex = NO_INDEX;
        m_animations.clear();

        robot2D::Image image{};
        if(!image.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load image by path {0}", message.filePath);
            return;
        }

        m_view -> onLoadImage(std::move(image));
        auto* msg = m_messageBus.postMessage<AnimationPanelLoadEmptyMessage>(MessageID::AnimationPanelLoad);
        msg -> needAddAnimation = true;
        m_view -> updateAnimation(nullptr);
    }

    void ViewerManager::onLoadXml(const LoadXmlMessage& message) {
        m_currentAnimation = 0;
        m_updateIndex = NO_INDEX;
        m_animations.clear();

        SpriteSheet spriteSheet;
        if(!spriteSheet.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load spriteSheet by path {0}", message.filePath);
            return;
        }

        std::filesystem::path p{message.filePath};
        p.remove_filename();
        p.assign(spriteSheet.getTexturePath());

        robot2D::Image image{};
        if(!image.loadFromFile(p.string())) {
            RB_ERROR("Can't load image by path {0}", p.string());
            return;
        }

        auto result = m_view -> onLoadAnimation(std::move(image), spriteSheet.getAnimations());
        if(!result.first)
            return;

        m_messageBus.postMessage<AnimationPanelLoadEmptyMessage>(MessageID::AnimationPanelLoad);
        for(const auto& animation: spriteSheet.getAnimations()) {
            m_animations.emplace_back(ViewerAnimation{animation, result.second});
            auto* msg = m_messageBus.postMessage<AnimationPanelLoadMessage>(MessageID::AnimationPanelAddAnimation);
            msg -> name = animation.title;
        }

        m_view -> updateAnimation(&m_animations[m_currentAnimation]);
    }



    void ViewerManager::undo() {
        m_commandStack.undo();
    }

    void ViewerManager::redo() {
        m_commandStack.redo();
    }

    void ViewerManager::deleteFrame() {
        if(m_currentAnimation != NO_INDEX && m_updateIndex != NO_INDEX) {
            auto collider = m_animations[m_currentAnimation][m_updateIndex];
            if(collider.state != Collider::State::Selected)
                return;

            m_animations[m_currentAnimation].eraseFrame(m_updateIndex);

            collider.borderColor = robot2D::Color::Green;
            m_commandStack.addCommand<DeleteFrameCommand>(
                    m_animations[m_currentAnimation],
                    collider,
                    m_updateIndex
            );

            m_updateIndex = NO_INDEX;
            return;
        }
    }

    void ViewerManager::processFrames(const robot2D::FloatRect& clipRegion,
                                      const robot2D::vec2f& worldPosition,
                                      robot2D::Image& image) {
        auto collider = viewer::Collider{};
        if(m_updateIndex == NO_INDEX) {
            collider.setRect(clipRegion);
            if(collider.notZero()) {
                auto&& frames = SpriteCutter{}.cutFrames(
                        {clipRegion.lx, clipRegion.ly, clipRegion.width, clipRegion.height},
                        image,
                        worldPosition
                );

                frames.erase(
                        std::unique(frames.begin(), frames.end()),
                        frames.end());
                std::sort(frames.begin(), frames.end());

                for(const auto& frame: frames) {
                    collider.setRect({frame.lx, frame.ly, frame.width, frame.height});
                    m_commandStack.addCommand<AddFrameCommand>(m_animations[m_currentAnimation], collider);
                    m_animations[m_currentAnimation].addFrame(collider, worldPosition);
                }
            }
        }
        else {
            m_animations[m_currentAnimation][m_updateIndex].showMovePoints = false;
            if(collider.notZero() && collider.state == Collider::State::Moving) {
                m_animations[m_currentAnimation][m_updateIndex].setRect(clipRegion);
            }
        }
    }

    std::pair<bool, int> ViewerManager::getCollisionPair(const robot2D::vec2f& point) {
        auto result = m_animations[m_currentAnimation].contains(point);
        if(result.first)
            m_updateIndex = result.second;
        else
            return {false, NO_INDEX};
        return m_animations[m_currentAnimation].contains(point);
    }

    void ViewerManager::setCollider(const robot2D::FloatRect& collidingRect) {
        if(m_updateIndex >= 0)
            m_animations[m_currentAnimation][m_updateIndex].setRect(collidingRect);
    }

    Collider& ViewerManager::getCollider(int index) {
        //TODO(a.raag): Add asserts
        //assert(index < m_animations[m_currentAnimation].getSize());
        return m_animations[m_currentAnimation][index];
    }


} // namespace viewer