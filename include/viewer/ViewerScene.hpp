#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include <robot2D/Core/MessageBus.hpp>

#include "ViewerView.hpp"
#include "ViewerManager.hpp"
#include "PanelManager.hpp"
#include "Camera2D.hpp"

#include "EventBinder.hpp"
#include "MessageDispather.hpp"
#include "ViewerAnimation.hpp"
#include "Messages.hpp"

namespace viewer {

    class ViewerScene {
    public:
        ViewerScene(robot2D::MessageBus& messageBus, MessageDispatcher& dispatcher);
        ViewerScene(const ViewerScene& other) = delete;
        ViewerScene& operator=(const ViewerScene& other) = delete;
        ViewerScene(ViewerScene&& other) = delete;
        ViewerScene& operator=(ViewerScene&& other) = delete;
        ~ViewerScene() = default;

        void setup(robot2D::RenderWindow* window);

        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void render();
    private:
        /// on Event
        void onMousePressed(const robot2D::Event& event);
        void onMouseReleased(const robot2D::Event& event);
        void onKeyboardPressed(const robot2D::Event& event);
    private:
        void setupResources();
        void setupBindings();
    private:
        robot2D::RenderWindow* m_window;
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;

        ViewerManager m_Manager;
        ViewerView m_View;

        PanelManager m_panelManager;
        EventBinder m_eventBinder;

        bool m_leftMousePressed = false;
    };


} // namespace viewer
