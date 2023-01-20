#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include "MessageDispather.hpp"
#include "Messages.hpp"
#include "CommandStack.hpp"
#include "ViewerAnimation.hpp"

namespace viewer {
    class IViewerManager {
    public:
        virtual ~IViewerManager() = 0;
        virtual void setupMessages();
    };

    class ViewerManager {
    public:
        ViewerManager(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher);
        ~ViewerManager() = default;

        void setupMessages();

        void undo();
        void redo();
        void deleteFrame();
    private:
        void onAddAnimation(const AddAnimationMessage& message);
        void onSwitchAnimation(const SwitchAnimationMessage& message);
        void onDeleteAnimation(const DeleteAnimationMessage& message);
        void onSaveAnimations(const SaveAnimationsMessage& message);

        void onLoadImage(const LoadImageMessage& message);
        void onLoadXml(const LoadXmlMessage& message);
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;

        CommandStack m_commandStack;
        std::vector<ViewerAnimation> m_animations;

        int updateIndex = -1;
        int m_currentAnimation = -1;
    };
}