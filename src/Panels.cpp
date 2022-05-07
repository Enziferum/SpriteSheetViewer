#include <robot2D/Extra/Api.hpp>
#include "viewer/Panels.hpp"

IPanel::IPanel(const PanelID& id): m_id(id) {}

IPanel::~IPanel() noexcept {}


ViewerPanel::ViewerPanel(): IPanel(PanelIDS::ViewerPanelID),
m_animation(nullptr) {}

void ViewerPanel::setSpriteSheetAnimation(SpriteSheetAnimation* animation) {
    m_animation = animation;
}

void ViewerPanel::update(float dt) {
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoBringToFrontOnFocus;


//    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
//    // Based on your use case you may want one of the other.
//    const ImGuiViewport* viewport = ImGui::GetMainViewport();
//    ImGui::SetNextWindowPos(viewport->WorkPos);
//    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Viewer");

    const float min_value = 1.f;
    const float max_value = 100.f;
    if (!ImGui::SliderFloat("Speed", &m_animation->getSpeed(), min_value, max_value)) {}


    ImGui::End();

    if(ImGui::Begin("Demo")) {
        auto sprite = m_animation -> getSprite();
        if(sprite)
            ImGui::AnimatedImage(*sprite, {150, 150});
    }
    ImGui::End();
}

MenuPanel::MenuPanel(): IPanel(PanelIDS::MenuPanelID) {

}

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
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
}

