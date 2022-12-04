#include <viewer/panels/IPanel.hpp>

namespace viewer {
    IPanel::~IPanel() {}

    IPanel::IPanel(PanelID panelId): m_id(panelId) {}
}