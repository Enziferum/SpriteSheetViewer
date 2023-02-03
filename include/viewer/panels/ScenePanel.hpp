#pragma once

#include <utility>
#include <robot2D/Core/MessageBus.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include <viewer/Camera2D.hpp>
#include <viewer/MessageDispather.hpp>
#include <viewer/Messages.hpp>

#include "IPanel.hpp"

namespace viewer {
    class ScenePanel: public IPanel {
    public:
        ScenePanel(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher, Camera2D& camera2D);
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
        void onNewTab(const NewTabMessage& message);

        void guiRender();
        void windowFunction();
        void showScene();
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        Camera2D& m_camera2D;
        robot2D::FrameBuffer::Ptr m_framebuffer{nullptr};
        robot2D::vec2u m_ViewportSize{};
        robot2D::vec2f m_ViewportBounds[2];

        std::vector<std::string> m_tabNames;
        std::unordered_map<int, bool> m_tabIndices;
        int m_lastOpenIndex = -1;
    };
}