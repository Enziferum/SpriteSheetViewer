#include <viewer/panels/ScenePanel.hpp>
#include <robot2D/imgui/Api.hpp>
#include <viewer/macro.hpp>
#include <viewer/Messages.hpp>

namespace viewer {

    ScenePanel::ScenePanel(robot2D::MessageBus& messageBus, Camera2D& camera2D):
        IPanel(typeid(ScenePanel)),
        m_messageBus{messageBus},
        m_camera2D{camera2D} {

    }

    void ScenePanel::update(float dt) {
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) ||
                ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            auto[mx, my] = ImGui::GetMousePos();
            mx -= m_ViewportBounds[0].x;
            my -= m_ViewportBounds[0].y;
        }

        guiRender();
    }

    void ScenePanel::guiRender() {
        robot2D::WindowOptions windowOptions = robot2D::WindowOptions {
                {
                        {ImGuiStyleVar_WindowPadding, {0, 0}}
                },
                {}
        };
        // ImGuiWindowFlags_NoTitleBar
        windowOptions.flagsMask =  ImGuiWindowFlags_NoScrollbar;
        windowOptions.name = "##Scene";
        robot2D::createWindow(windowOptions, BIND_CLASS_FN(windowFunction));
    }

    bool ScenePanel::isMouseOver() const {
        return m_mouseIsOver;
    }

    void ScenePanel::windowFunction() {
        checkMouseHover();

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x,
                                viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x,
                                viewportMaxRegion.y + viewportOffset.y };

        //  m_panelFocused = ImGui::IsWindowFocused();
        // m_panelHovered = ImGui::IsWindowHovered();

        /// TODO: @a.raag switch mode of camera ///
        auto ViewPanelSize = ImGui::GetContentRegionAvail();

        if(m_ViewportSize != robot2D::vec2u { ViewPanelSize.x, ViewPanelSize.y}) {
            m_ViewportSize = {ViewPanelSize.x, ViewPanelSize.y};
            m_framebuffer -> Resize(m_ViewportSize);
            m_camera2D.resetViewport(m_ViewportSize.as<float>());

            auto* msg = m_messageBus.postMessage<SceneViewportMessage>(MessageID::SceneViewportSize);
            msg -> newSize = {ViewPanelSize.x, ViewPanelSize.y};
        }

        robot2D::RenderFrameBuffer(m_framebuffer, m_ViewportSize.as<float>());
    }


} // namespace viewer