#include <robot2D/imgui/Api.hpp>
#include <viewer/panels/IPanel.hpp>

namespace viewer {
    IPanel::~IPanel() {}

    IPanel::IPanel(PanelID panelId): m_id(panelId) {}

    void IPanel::checkMouseHover() {
        m_mouseIsOver = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();
    }

}