#include <robot2D/imgui/Api.hpp>
#include <viewer/panels/MenuPanel.hpp>
#include <viewer/FileDialog.hpp>

namespace viewer {
    MenuPanel::MenuPanel(): IPanel(typeid(MenuPanel)) {}

    void MenuPanel::update(float dt) {
        if(ImGui::BeginMainMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                showFileMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void MenuPanel::showFileMenu() {
        if (ImGui::MenuItem("Open", "Ctrl+O")) {
            // "Save" nullptr, 0, nullptr, nullptr
            auto path = openFileDialog("Load", "*.png", "");
            if(path.empty()) {
                return;
            }
        }

    }
}