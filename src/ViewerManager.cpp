#include <unordered_set>
#include <viewer/ViewerManager.hpp>
#include <viewer/SpriteCutter.hpp>
#include <viewer/SpriteSheet.hpp>
#include <viewer/ISceneView.hpp>
#include <viewer/Defines.hpp>
#include <viewer/Utils.hpp>

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

        m_messageDispatcher.onMessage<NewTabMessage>(MessageID::NewTab,
                                                     BIND_CLASS_FN(onNewTab));
        m_messageDispatcher.onMessage<SwitchTabMessage>(MessageID::SwitchTab,
                                                     BIND_CLASS_FN(onSwitchTab));
        m_messageDispatcher.onMessage<CloseTabMessage>(MessageID::CloseTab,
                                                     BIND_CLASS_FN(onCloseTab));

        m_messageDispatcher.onMessage<LoadImageMessage>(MessageID::LoadImage, BIND_CLASS_FN(onLoadImage));

        m_messageDispatcher.onMessage<LoadXmlMessage>(MessageID::LoadXml, BIND_CLASS_FN(onLoadXml));
    }


    void ViewerManager::onAddAnimation(const AddAnimationMessage& message) {
        ViewerAnimation viewerAnimation{};
        viewerAnimation.getAnimation().title = message.name;

        m_tabs[m_currentTab].addAnimation(std::move(viewerAnimation));
        m_currentAnimation = m_tabs[m_currentTab].getSize() - 1;

        auto animation = m_tabs[m_currentTab][m_currentAnimation].getAnimation();
        m_view -> updateView(m_currentTab, &m_tabs[m_currentTab][m_currentAnimation]);
    }

    void ViewerManager::onSaveAnimations(const SaveAnimationsMessage& message) {
        SpriteSheet spriteSheet;
        AnimationList animations;
        for(const auto& animation: m_tabs[m_currentTab].getAnimations())
            animations.emplace_back(animation.getAnimation());
        auto maskColor = m_view -> getImageMaskColor();
        if(!spriteSheet.saveToFile(message.filePath, m_texturePath, maskColor, animations)) {
            RB_CRITICAL("Can't save animation");
            THROW("Can't save animation");
        }
    }

    void ViewerManager::onDeleteAnimation(const DeleteAnimationMessage& message) {
       // assert(message.deleteIndex < static_cast<int>(m_animations.size()));
        m_tabs[m_currentTab].eraseAnimation(message.deleteIndex);
        m_currentAnimation = message.switchToIndex;

        auto animation = m_tabs[m_currentTab][m_currentAnimation].getAnimation();
        m_view -> updateView(m_currentTab, &m_tabs[m_currentTab][m_currentAnimation]);
    }

    void ViewerManager::onSwitchAnimation(const SwitchAnimationMessage& message) {
        m_currentAnimation = message.indexTo;

        auto animation = m_tabs[m_currentTab][m_currentAnimation].getAnimation();
        m_view -> updateView(m_currentTab, &m_tabs[m_currentTab][m_currentAnimation]);
    }

    void ViewerManager::onLoadImage(const LoadImageMessage& message) {
        m_currentAnimation = NO_INDEX;
        m_updateIndex = NO_INDEX;
        m_tabs[m_currentTab].clearAnimations();
        m_texturePath = message.filePath;

        robot2D::Image image{};
        if(!image.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load image by path {0}", message.filePath);
            THROW("Can't load image by path");
        }

        m_view -> onLoadImage(std::move(image));
        auto* msg = m_messageBus.postMessage<AnimationPanelLoadEmptyMessage>(MessageID::AnimationPanelLoad);
        msg -> needAddAnimation = true;
        m_view -> updateView(m_currentTab, nullptr);
    }

    void ViewerManager::onLoadXml(const LoadXmlMessage& message) {
        m_currentAnimation = 0;
        m_updateIndex = NO_INDEX;
        m_tabs[m_currentTab].clearAnimations();

        SpriteSheet spriteSheet;
        if(!spriteSheet.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load spriteSheet by path {0}", message.filePath);
            THROW("Can't load spriteSheet by path");
        }

        m_texturePath = spriteSheet.getTexturePath();

        robot2D::Image image{};
        if(!image.loadFromFile(spriteSheet.getTexturePath())) {
            RB_ERROR("Can't load image by path {0}", spriteSheet.getTexturePath());
            THROW("Can't load image by path");
        }

        auto result = m_view -> onLoadAnimation(std::move(image));
        if(!result.first)
            return;

        m_messageBus.postMessage<AnimationPanelLoadEmptyMessage>(MessageID::AnimationPanelLoad);
        for(const auto& animation: spriteSheet.getAnimations()) {
            m_tabs[m_currentTab].addAnimation(ViewerAnimation{animation, result.second});
            auto* msg = m_messageBus.postMessage<AnimationPanelLoadMessage>(MessageID::AnimationPanelAddAnimation);
            msg -> name = animation.title;
        }

        m_view -> updateView(m_currentTab, &m_tabs[m_currentTab][m_currentAnimation]);
    }

    void ViewerManager::undo() {
        m_commandStack.undo();
    }

    void ViewerManager::redo() {
        m_commandStack.redo();
    }

    void ViewerManager::deleteFrame() {
        if(m_currentAnimation != NO_INDEX && m_updateIndex != NO_INDEX) {
            auto collider = m_tabs[m_currentTab][m_currentAnimation][m_updateIndex];
            if(collider.state != Collider::State::Selected)
                return;

            m_tabs[m_currentTab][m_currentAnimation].eraseFrame(m_updateIndex);

            collider.borderColor = robot2D::Color::Green;
            m_commandStack.addCommand<DeleteFrameCommand>(
                    m_tabs[m_currentTab][m_currentAnimation],
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
        if (m_updateIndex == NO_INDEX) {
            collider.setRect(clipRegion);
            if (collider.notZero()) {
                if (m_cutMode == CutMode::Automatic) {
                    auto &&frames = SpriteCutter{}.cutFrames(
                            clipRegion.as<unsigned int>(),
                            image,
                            worldPosition
                    );

                    std::unordered_set<robot2D::IntRect, util::HashFunction> uniqueFrames;
                    for (const auto &frame: frames)
                        uniqueFrames.insert(frame);

                    std::vector<robot2D::IntRect> sortFrames;
                    sortFrames.assign(uniqueFrames.begin(), uniqueFrames.end());
                    std::sort(sortFrames.begin(), sortFrames.end(), [](const robot2D::IntRect &l,
                                                                       const robot2D::IntRect &r) {
                        return l.lx < r.lx;
                    });

                    for (const auto &frame: sortFrames) {
                        collider.setRect({frame.lx, frame.ly, frame.width, frame.height});
                        m_commandStack.addCommand<AddFrameCommand>(m_tabs[m_currentTab][m_currentAnimation], collider);
                        m_tabs[m_currentTab][m_currentAnimation].addFrame(collider, worldPosition);
                    }
                } else {
//                    collider.setRect({frame.lx, frame.ly, frame.width, frame.height});
//                    m_commandStack.addCommand<AddFrameCommand>(m_tabs[m_currentTab][m_currentAnimation], collider);
//                    m_tabs[m_currentTab][m_currentAnimation].addFrame(collider, worldPosition);
                }
            } else {
                m_tabs[m_currentTab][m_currentAnimation][m_updateIndex].showMovePoints = false;
                if (collider.notZero() && collider.state == Collider::State::Moving) {
                    m_tabs[m_currentTab][m_currentAnimation][m_updateIndex].setRect(clipRegion);
                }
            }
        }
    }

    std::pair<bool, int> ViewerManager::getCollisionPair(const robot2D::vec2f& point) {
        auto result = m_tabs[m_currentTab][m_currentAnimation].contains(point);
        if(result.first)
            m_updateIndex = result.second;
        else
            return {false, NO_INDEX};
        return m_tabs[m_currentTab][m_currentAnimation].contains(point);
    }

    void ViewerManager::setCollider(const robot2D::FloatRect& collidingRect) {
        if(m_updateIndex >= 0)
            m_tabs[m_currentTab][m_currentAnimation][m_updateIndex].setRect(collidingRect);
    }

    Collider& ViewerManager::getCollider(int index) {
        //TODO(a.raag): Add asserts
        //assert(index < m_animations[m_currentAnimation].getSize());
        return m_tabs[m_currentTab][m_currentAnimation][index];
    }

    void ViewerManager::onNewTab(const NewTabMessage& message) {
        m_tabs.emplace_back(Tab{});
        m_currentTab = m_tabs.size() - 1;
        m_currentAnimation = NO_INDEX;
        m_updateIndex = NO_INDEX;

        auto* msg = m_messageBus.postMessage<AnimationPanelLoadEmptyMessage>(MessageID::AnimationPanelLoad);
        msg -> needAddAnimation = true;
        m_view -> updateView(m_currentTab, nullptr);
        m_view -> resetNames({});
    }

    void ViewerManager::onSwitchTab(const SwitchTabMessage& message) {
        m_currentTab = message.switchToIndex;
        m_currentAnimation = 0;
        m_updateIndex = NO_INDEX;

        m_view -> updateView(m_currentTab, &m_tabs[m_currentTab][m_currentAnimation]);
        std::vector<std::string> actualNames;
        for(const auto& animation: m_tabs[m_currentTab].getAnimations())
            actualNames.emplace_back(animation.getAnimation().title);
        m_view -> resetNames(actualNames);
    }

    void ViewerManager::onCloseTab(const CloseTabMessage& message) {
        m_currentAnimation = 0;
    }


} // namespace viewer