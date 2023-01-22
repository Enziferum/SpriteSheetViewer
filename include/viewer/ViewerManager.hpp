#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include "MessageDispather.hpp"
#include "Messages.hpp"
#include "CommandStack.hpp"
#include "ViewerAnimation.hpp"

namespace viewer {
    class ISceneView;
    class IViewerManager {
    public:
        virtual ~IViewerManager() = 0;
        virtual void setupMessages();
    };

    class ViewerManager {
    public:
        ViewerManager(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher);
        ~ViewerManager() = default;

        void setup(ISceneView* view);

        void cutFrames(const robot2D::FloatRect& clipRegion,
                       const robot2D::vec2f& worldPosition);

        void setCollider(const robot2D::FloatRect& collidingRect);
        Collider& getCollider(int index);

        void undo();
        void redo();
        void deleteFrame();
        std::pair<bool, int> getCollisionPair(const robot2D::vec2f& point);

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
        ISceneView* m_view;

        CommandStack m_commandStack;
        std::vector<ViewerAnimation> m_animations;

        int updateIndex = -1;
        int m_currentAnimation = -1;
    };
}