#include <robot2D/Util/Logger.hpp>

#include <robot2D/imgui/Api.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/macro.hpp>

namespace viewer {

    ViewerPanel::ViewerPanel():
        IPanel(typeid(ViewerPanel)),
        m_animation(nullptr) {}

    void ViewerPanel::setSpriteSheetAnimation(SpriteSheetAnimation* animation) {
        m_animation = animation;
    }

    void ViewerPanel::update(float dt) {
        (void)dt;

        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove
                                        | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings
                                        | ImGuiWindowFlags_NoBringToFrontOnFocus;

        robot2D::WindowOptions windowOptions{};
        windowOptions.flagsMask = 0;
        windowOptions.name = "Viewer";

        robot2D::createWindow(windowOptions, BIND_CLASS_FN(guiUpdate));
    }

    void ViewerPanel::guiUpdate() {
        checkMouseHover();

        if(!m_animation )
            return;
        auto* render = m_animation -> getAnimationRender();
        if(!render || m_animation -> getFramesCount() == 0)
            return;

        auto contentSize = ImGui::GetWindowSize();
        robot2D::vec2f imageSize = { contentSize.x / 2.F, contentSize.y / 2.F };
        ImGui::SetCursorPos({(contentSize.x - imageSize.x) / 2.F, (contentSize.y - imageSize.y) / 2.F});
        robot2D::AnimatedImage(*render, imageSize);
    }
}