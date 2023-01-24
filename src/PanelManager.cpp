#include <robot2D/imgui/Api.hpp>
#include <viewer/PanelManager.hpp>

namespace viewer {

    namespace {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    }

    PanelManager::PanelManager(): m_panels{} {}

    void PanelManager::handleEvents(const robot2D::Event& event) {}

    void PanelManager::update(float dt) {
        currDt = dt;
    }

    bool PanelManager::isMouseIsOver() const {
        return std::any_of(m_panels.begin(), m_panels.end(), [](const auto& panel) {
            return panel -> isMouseOver();
        });
    }

    void PanelManager::dockingUpdate() {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
                        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport -> WorkPos);
        ImGui::SetNextWindowSize(viewport -> WorkSize);
        ImGui::SetNextWindowViewport(viewport -> ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.F);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.F);

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        robot2D::WindowOptions dockWindowOptions{};
        dockWindowOptions.flagsMask = window_flags;
        dockWindowOptions.name = "Scene";

        robot2D::createWindow(dockWindowOptions, [this]() {

            ImGui::PopStyleVar(2);

            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),
                                 dockspace_flags);
            }

        });
    }

    void PanelManager::render() {
        dockingUpdate();
        for(auto& panel: m_panels)
            panel -> update(currDt);
    }

}
