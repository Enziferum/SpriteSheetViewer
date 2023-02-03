#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include <robot2D/Core/MessageBus.hpp>

#include "MessageDispather.hpp"
#include "ISceneView.hpp"
#include "ViewerManager.hpp"
#include "ViewerView.hpp"
#include "EventBinder.hpp"
#include "PanelManager.hpp"
#include "Camera2D.hpp"
#include "Collider.hpp"

namespace viewer {

    class ViewerScene: public ISceneView {
    public:
        ViewerScene(robot2D::MessageBus& messageBus, MessageDispatcher& dispatcher);
        ViewerScene(const ViewerScene& other) = delete;
        ViewerScene& operator=(const ViewerScene& other) = delete;
        ViewerScene(ViewerScene&& other) = delete;
        ViewerScene& operator=(ViewerScene&& other) = delete;
        ~ViewerScene() override = default;

        void setup(robot2D::RenderWindow* window);
        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void render();

        void updateView(std::size_t tabIndex, ViewerAnimation* animation) override;
        void onLoadImage(robot2D::Image&& image, std::size_t newIndex) override;
        std::pair<bool, robot2D::vec2f>

        onLoadAnimation(robot2D::Image&& image) override;
        void resetNames(const std::vector<std::string>& names) override;


        robot2D::Color getImageMaskColor() const override { return m_View.getImageMaskColor();}
    private:
        /// on Event
        void onMouseMoved(const robot2D::Event::MouseMoveEvent& event);
        void onMousePressed(const robot2D::Event::MouseButtonEvent& event);
        void onMouseReleased(const robot2D::Event::MouseButtonEvent& event);
        void onKeyboardPressed(const robot2D::Event::KeyboardEvent& event);
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

        Camera2D m_camera2D;
        robot2D::FrameBuffer::Ptr m_frameBuffer;
        Collider m_selectCollider;
        ViewerAnimation* m_currentAnimation{nullptr};
        bool m_leftMousePressed = false;
    };


} // namespace viewer
