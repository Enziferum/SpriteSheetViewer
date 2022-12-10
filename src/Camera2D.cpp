#include <viewer/Camera2D.hpp>

namespace viewer {

    namespace {
        float zoomOffset = 1.F;
        float zoomMultiplier = 0.1F;
    }



    void Camera2D::resetViewport(const robot2D::vec2f& windowSize) {
        m_view.reset({0, 0, windowSize.x, windowSize.y});
        m_mousePos = {windowSize / 2.F};
    }

    void Camera2D::handleEvents(const robot2D::Event& event) {
        if(event.type == robot2D::Event::MouseWheel) {
            m_zoom = zoomOffset + -event.wheel.scroll_y * zoomMultiplier;
            m_view.zoom(m_zoom);
        }
    }

    void Camera2D::update(float dt, robot2D::RenderWindow* window) {
        (void)dt;

        constexpr float deltaOffset = 0.5F;

        auto mousePos = window -> getMousePos();
        robot2D::vec2f delta = (mousePos - m_mousePos) * deltaOffset;
        m_mousePos = mousePos;

        if(window -> isMousePressed(robot2D::Mouse::MouseMiddle)) {
            auto center = m_view.getCenter();
            center.x += delta.x * 2.F;
            center.y += delta.y * 2.F;
            m_view.setCenter(center);
        }

    }

}