#include <robot2D/Extra/Api.hpp>
#include <robot2D/Util/Logger.hpp>
#include <viewer/panels/ScenePanel.hpp>

namespace viewer {

    ScenePanel::ScenePanel(Camera2D& camera2D):
        IPanel(typeid(ScenePanel)),
        m_camera2D{camera2D} {

    }

    void ScenePanel::update(float dt) {
        if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) ||
                ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            auto[mx, my] = ImGui::GetMousePos();
            mx -= m_ViewportBounds[0].x;
            my -= m_ViewportBounds[0].y;

            lastMousePos = m_camera2D.mapPixelToCoords({mx, my});

            RB_INFO("Formatted Point by ScenePanel {0}: {1}", mx, my);
        }

        guiRender();
    }

    void ScenePanel::guiRender() {
        ImGui::WindowOptions windowOptions = ImGui::WindowOptions {
                {
                        {ImGuiStyleVar_WindowPadding, {0, 0}}
                },
                {}
        };
        // ImGuiWindowFlags_NoTitleBar
        windowOptions.flagsMask =  ImGuiWindowFlags_NoScrollbar;
        windowOptions.name = "##Scene";
        ImGui::createWindow(windowOptions, [this]() {

            auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
            auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
            auto viewportOffset = ImGui::GetWindowPos();
            m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
            m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

            //  m_panelFocused = ImGui::IsWindowFocused();
            // m_panelHovered = ImGui::IsWindowHovered();

            /// TODO: @a.raag switch mode of camera ///
            auto ViewPanelSize = ImGui::GetContentRegionAvail();

            if(m_ViewportSize != robot2D::vec2u { ViewPanelSize.x, ViewPanelSize.y}) {
                m_ViewportSize = {ViewPanelSize.x, ViewPanelSize.y};
                m_framebuffer -> Resize(m_ViewportSize);
                m_camera2D.resetViewport(m_ViewportSize.as<float>());
            }

            ImGui::RenderFrameBuffer(m_framebuffer, m_ViewportSize.as<float>());
        });
    }


} // namespace viewer