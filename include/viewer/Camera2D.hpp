#pragma once

#include <robot2D/Graphics/View.hpp>
#include <robot2D/Graphics/Image.hpp>
#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>

namespace viewer {

    class Camera2D {
    public:
        Camera2D() = default;
        ~Camera2D() = default;

        void setRenderTarget(const robot2D::RenderTarget* renderTarget);
        robot2D::vec2f mapPixelToCoords(const robot2D::vec2f& mousePos) const;
        robot2D::vec2f mapPixelToCoords(const robot2D::vec2f& point,
                                        robot2D::FrameBuffer::Ptr frameBuffer) const;

        void resetViewport(const robot2D::vec2f& windowSize);

        const robot2D::View& getCameraView() const {
            return m_view;
        }

        void handleEvents(const robot2D::Event& event);
        void update(float dt, robot2D::RenderWindow* window);
    private:
        robot2D::IntRect getViewport(robot2D::vec2i size) const;
    private:
        robot2D::View m_view{};
        robot2D::vec2f m_mousePos{};
        float m_zoom{0.F};
        const robot2D::RenderTarget* m_renderTarget{nullptr};
    };
}