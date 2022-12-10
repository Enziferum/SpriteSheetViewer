#pragma once

#include <robot2D/Graphics/FrameBuffer.hpp>
#include <viewer/Camera2D.hpp>
#include "IPanel.hpp"

namespace viewer {
    class ScenePanel: public IPanel {
    public:
        ScenePanel(Camera2D& camera2D);
        ~ScenePanel() override = default;

        void setFramebuffer(robot2D::FrameBuffer::Ptr frameBuffer) {
            m_framebuffer = frameBuffer;
        }
        void update(float dt) override;

        robot2D::vec2f getPanelBounds() const {
            return lastMousePos;
        }
    private:
        void guiRender();
    private:
        Camera2D& m_camera2D;
        robot2D::FrameBuffer::Ptr m_framebuffer{nullptr};
        robot2D::vec2u m_ViewportSize{};
        robot2D::vec2f lastMousePos{};
        robot2D::vec2f m_ViewportBounds[2];
    };
}