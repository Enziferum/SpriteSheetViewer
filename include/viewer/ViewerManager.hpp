#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include "MessageDispather.hpp"
#include "Messages.hpp"
#include "CommandStack.hpp"
#include "ViewerAnimation.hpp"
#include "Defines.hpp"
#include "NamesContainer.hpp"
#include "TabContainer.hpp"

namespace viewer {

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

        void update();

        void undo();
        void redo();
        void deleteFrame();
        std::pair<bool, int> getCollisionPair(const robot2D::vec2f& point);

        void setCutMode();
        int getCurrentTab() const { return m_currentTab; }

        std::vector<IDocument::Ptr>& getDocuments() {
            return m_docs;
        }

        IAddGetName* getNamesContainer() {
            return &m_namesContainer;
        }
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
        void addNewTab();
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        ISceneView* m_view{nullptr};

        std::vector<CommandStack> m_commandStack;
        std::vector<TabContainer::Ptr> m_tabs;
        std::vector<IDocument::Ptr> m_docs;

        int m_currentTab = NO_INDEX;
        int m_updateIndex = NO_INDEX;
        int m_currentAnimation = NO_INDEX;

        CutMode m_cutMode = CutMode::Automatic;
        NamesContainer m_namesContainer;
    };
} // namespace viewer