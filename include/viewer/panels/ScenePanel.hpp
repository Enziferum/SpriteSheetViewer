#pragma once

#include <robot2D/Graphics/FrameBuffer.hpp>
#include <utility>
#include <viewer/Camera2D.hpp>
#include <robot2D/Core/MessageBus.hpp>
#include "IPanel.hpp"

namespace viewer {
    class ScenePanel: public IPanel {
    public:
        ScenePanel(robot2D::MessageBus& messageBus, Camera2D& camera2D);
        ~ScenePanel() override = default;

        void update(float dt) override;

        void setFramebuffer(robot2D::FrameBuffer::Ptr frameBuffer) {
            m_framebuffer = std::move(frameBuffer);
        }

        [[nodiscard]]
        robot2D::vec2f getPanelBounds() const {
            return m_ViewportBounds[0];
        }

        bool isMouseOver() const override;
    private:
        void guiRender();
        void windowFunction();
    private:
        robot2D::MessageBus& m_messageBus;
        Camera2D& m_camera2D;
        robot2D::FrameBuffer::Ptr m_framebuffer{nullptr};
        robot2D::vec2u m_ViewportSize{};
        robot2D::vec2f m_ViewportBounds[2];
    };
}