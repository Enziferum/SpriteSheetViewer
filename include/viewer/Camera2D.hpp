#pragma once

#include <robot2D/Graphics/View.hpp>
#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>

namespace viewer {

    class Camera2D {
    public:
        Camera2D() = default;
        ~Camera2D() = default;

        void setRenderTarget(const robot2D::RenderTarget* renderTarget) {
            m_renderTarget = renderTarget;
        }

        robot2D::vec2f mapPixelToCoords(const robot2D::vec2f& mousePos) const {
            auto pos = mousePos;
            return m_renderTarget->mapPixelToCoords(pos.as<int>(), m_view);
        }

        robot2D::vec2f mapPixelToCoords(const robot2D::vec2f& point, robot2D::FrameBuffer::Ptr frameBuffer) const {
            robot2D::vec2f normalized;
            auto port = getViewport(frameBuffer -> getSpecification().size);
            robot2D::FloatRect viewport = {port.lx, port.ly, port.width, port.height};
            normalized.x       = -1.f + 2.f * (static_cast<float>(point.x) - viewport.lx) / viewport.width;
            normalized.y       = 1.f - 2.f * (static_cast<float>(point.y) - viewport.ly) / viewport.height;

            // Then transform by the inverse of the view matrix
            return m_view.getInverseTransform().transformPoint(normalized);
        }

        void resetViewport(const robot2D::vec2f& windowSize);

        void handleEvents(const robot2D::Event& event);

        void update(float dt, robot2D::RenderWindow* window);

        const robot2D::View& getCameraView() const {
            return m_view;
        }
    private:
        robot2D::IntRect getViewport(robot2D::vec2i size) const {
            float width  = static_cast<float>(size.x);
            float height = static_cast<float>(size.y);
            const robot2D::FloatRect& viewport = m_view.getViewport();

            return robot2D::IntRect(static_cast<int>(0.5F + width  * viewport.lx),
                           static_cast<int>(0.5F + height * viewport.ly),
                           static_cast<int>(0.5F + width  * viewport.width),
                           static_cast<int>(0.5F + height * viewport.height));
        }
    private:
        robot2D::View m_view{};
        robot2D::vec2f m_mousePos{};
        float m_zoom{0.F};
        const robot2D::RenderTarget* m_renderTarget{nullptr};
    };
}