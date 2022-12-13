#include <robot2D/Util/Logger.hpp>
#include <viewer/panels/ScenePanel.hpp>

#include <robot2D/imgui/Api.hpp>

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

            auto pos = ImGui::GetWindowPos();
            RB_INFO("ScenePanel POS {0}: {1}", pos.x, pos.y);

            lastMousePos = {mx, my};
            //lastMousePos = m_camera2D.mapPixelToCoords(lastMousePos);

            auto& view = m_camera2D.getCameraView();
            auto viewportSize = view.getSize();
            auto viewportCenter = view.getCenter();

            robot2D::FloatRect viewport {viewportCenter.x - viewportSize.x / 2.F,
                                         viewportCenter.y - viewportSize.y / 2.F,
                                         viewportSize.x, viewportSize.y};

            RB_INFO("M_VIEWPORT SIZE {0}, {1}", m_ViewportSize.x, m_ViewportSize.y);

            RB_INFO("Camera Viewport {0}, {1}, {2}, {3}", viewport.lx, viewport.ly, viewport.width, viewport.height);

            RB_INFO("Formatted Point by ScenePanel {0}: {1}", lastMousePos.x, lastMousePos.y);
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
        robot2D::createWindow(windowOptions, [this]() {

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
            }

            robot2D::RenderFrameBuffer(m_framebuffer, m_ViewportSize.as<float>());
        });
    }


} // namespace viewer