#include <filesystem>

#include <robot2D/imgui/Api.hpp>

#include <viewer/panels/MenuPanel.hpp>
#include <viewer/FileDialog.hpp>
#include <viewer/Messages.hpp>

namespace viewer {
    namespace fs = std::filesystem;

    MenuPanel::MenuPanel(robot2D::MessageBus& messageBus): IPanel(typeid(MenuPanel)),
    m_messageBus{messageBus}{}

    void MenuPanel::update(float dt) {
        (void)dt;
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
            auto&& path = openFileDialog("Load", ".png", "");
            if(path.empty())
                return;

            auto fspath = fs::path{path};
            if(fs::is_regular_file(fspath)) {
                if(fspath.extension() == ".png" || ".PNG") {
                    auto* msg = m_messageBus.postMessage<LoadImageMessage>(MessageID::LoadImage);
                    msg -> filePath = std::move(path);
                }

                if(fspath.extension() == ".xml") {
                    auto* msg = m_messageBus.postMessage<LoadXmlMessage>(MessageID::LoadXml);
                    msg -> filePath = std::move(path);
                }
            }
        }
    }
}