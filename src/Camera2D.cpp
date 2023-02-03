#include <cmath>
#include <viewer/Camera2D.hpp>

namespace viewer {

    namespace {
        constexpr const float zoomOffset = 1.F;
        constexpr const float zoomMultiplier = 0.1F;
    }

    void Camera2D::setRenderTarget(const robot2D::RenderTarget* renderTarget) {
        m_renderTarget = renderTarget;
    }

    robot2D::vec2f Camera2D::mapPixelToCoords(const robot2D::vec2f& mousePos) const {
        auto pos = mousePos;
        return m_renderTarget -> mapPixelToCoords(pos.as<int>(), m_view);
    }

    robot2D::vec2f Camera2D::mapPixelToCoords(const robot2D::vec2f& point,
                                    robot2D::FrameBuffer::Ptr frameBuffer) const {
        robot2D::vec2f normalized;
        auto port = getViewport(frameBuffer -> getSpecification().size);
        robot2D::FloatRect viewport = {
                static_cast<float>(port.lx),
                static_cast<float>(port.lx),
                static_cast<float>(port.width),
                static_cast<float>(port.height)
        };
        normalized.x = -1.f + 2.f * (static_cast<float>(point.x) - viewport.lx) / viewport.width;
        normalized.y = 1.f - 2.f * (static_cast<float>(point.y) - viewport.ly) / viewport.height;

        // Then transform by the inverse of the view matrix
        return m_view.getInverseTransform().transformPoint(normalized);
    }

    robot2D::IntRect Camera2D::getViewport(robot2D::vec2i size) const {
        float width  = static_cast<float>(size.x);
        float height = static_cast<float>(size.y);
        const robot2D::FloatRect& viewport = m_view.getViewport();

        return {
            static_cast<int>(0.5F + width  * viewport.lx),
            static_cast<int>(0.5F + height * viewport.ly),
            static_cast<int>(0.5F + width  * viewport.width),
            static_cast<int>(0.5F + height * viewport.height)
        };
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

        if(robot2D::Window::isMousePressed(robot2D::Mouse::MouseMiddle)) {
            auto center = m_view.getCenter();
            center.x += delta.x * 2.F;
            center.y += delta.y * 2.F;
            m_view.setCenter(center);
        }

    }

}