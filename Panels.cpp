#include <robot2D/Extra/Api.hpp>
#include <tfd/tinyfiledialogs.h>
#include "viewer/Panels.hpp"
#include <viewer/AnimationIO.hpp>

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

    ImGui::Begin("Viewer");

    const float min_value = 1.f;
    const float max_value = 100.f;
    auto sprite = m_animation -> getSprite();

    if(sprite) {
        ImGui::LabelText("Frame count ", "%i", m_animation -> getFramesCount());
        if (!ImGui::SliderFloat("Speed",
                                &m_animation -> getSpeed(), min_value, max_value)) {}

        static int counter = 0;
        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        ImGui::PushButtonRepeat(true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
        ImGui::SameLine(0.0f, spacing);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
        ImGui::PopButtonRepeat();
        ImGui::SameLine();
        ImGui::Text("%d", counter);

        ImGui::AnimatedImage(*sprite, {150, 150});
    }

    ImGui::End();
}

MenuPanel::MenuPanel():
    IPanel(PanelIDS::MenuPanelID) {

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

    if (ImGui::MenuItem("Save", "Ctrl+S")) {
        const char* path = tinyfd_saveFileDialog("Save", nullptr, 0, nullptr, nullptr);
        if(!path)
            return;

        viewer::AnimationIO animationIo{};
        //animationIo.saveToFile(path, m_animation -> getAnimations());
    }
}

