#pragma once

#include <robot2D/Graphics/View.hpp>
#include <robot2D/Graphics/RenderWindow.hpp>

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

        void resetViewport(const robot2D::vec2f& windowSize);

        void handleEvents(const robot2D::Event& event);

        void update(float dt, robot2D::RenderWindow* window);

        const robot2D::View& getCameraView() const {
            return m_view;
        }
    private:
        robot2D::View m_view{};
        robot2D::vec2f m_mousePos{};
        float m_zoom{0.F};
        const robot2D::RenderTarget* m_renderTarget{nullptr};
    };
}