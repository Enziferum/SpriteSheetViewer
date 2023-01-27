#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include "MessageDispather.hpp"
#include "Messages.hpp"
#include "CommandStack.hpp"
#include "ViewerAnimation.hpp"
#include "Defines.hpp"

namespace viewer {

    class Tab {
    public:
        ViewerAnimation& addAnimation(ViewerAnimation&& viewerAnimation) {
            return m_animations.emplace_back(viewerAnimation);
        }

        void eraseAnimation(std::size_t index) {
            assert(index < m_animations.size());
            if(m_animations.size() > 1)
                m_animations.erase(m_animations.begin() + index);
        }

        void clearAnimations() {
            m_animations.clear();
        }

        std::size_t getSize() const noexcept {
            return m_animations.size();
        }

        const std::vector<ViewerAnimation>& getAnimations() const {
            return m_animations;
        }

        ViewerAnimation& addAnimation(const Animation& animation, const robot2D::vec2f& worldPos = {}) {
            ViewerAnimation viewerAnimation{animation, worldPos};
            m_animations.emplace_back(viewerAnimation);
            return m_animations.back();
        }

        ViewerAnimation& operator[](std::size_t index) {
            return m_animations[index];
        }

        const ViewerAnimation& operator[](std::size_t index) const {
            return m_animations[index];
        }
    private:
        std::vector<ViewerAnimation> m_animations;
    };

    class ISceneView;
    class ViewerManager {
    public:
        enum class CutMode {
            Manual = 0,
            Automatic
        };
    public:
        ViewerManager(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher);
        ~ViewerManager() = default;

        void setup(ISceneView* view);

        void processFrames(const robot2D::FloatRect& clipRegion,
                           const robot2D::vec2f& worldPosition,
                           robot2D::Image& image);

        void setCollider(const robot2D::FloatRect& collidingRect);
        Collider& getCollider(int index);

        void undo();
        void redo();
        void deleteFrame();
        std::pair<bool, int> getCollisionPair(const robot2D::vec2f& point);

        void setCutMode() { if(m_cutMode == CutMode::Automatic) m_cutMode = CutMode::Manual; else m_cutMode = CutMode::Automatic;}
        int getCurrentTab() const { return m_currentTab; }

    private:
        void onAddAnimation(const AddAnimationMessage& message);
        void onSwitchAnimation(const SwitchAnimationMessage& message);
        void onDeleteAnimation(const DeleteAnimationMessage& message);
        void onSaveAnimations(const SaveAnimationsMessage& message);

        void onNewTab(const NewTabMessage& message);
        void onSwitchTab(const SwitchTabMessage& message);
        void onCloseTab(const CloseTabMessage& message);

        void onLoadImage(const LoadImageMessage& message);
        void onLoadXml(const LoadXmlMessage& message);
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        ISceneView* m_view{nullptr};

        CommandStack m_commandStack;
        std::vector<Tab> m_tabs;

        int m_currentTab = NO_INDEX;
        int m_updateIndex = NO_INDEX;
        int m_currentAnimation = NO_INDEX;

        std::string m_texturePath;
        CutMode m_cutMode = CutMode::Automatic;
    };
} // namespace viewer