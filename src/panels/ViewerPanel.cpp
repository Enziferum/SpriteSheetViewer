#include <robot2D/Util/Logger.hpp>
#include <robot2D/imgui/Api.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/Macro.hpp>

namespace viewer {

    ViewerPanel::ViewerPanel():
        IPanel(typeid(ViewerPanel)),
        m_animationSheet(nullptr) {}

    void ViewerPanel::setSpriteSheetAnimation(SpriteSheetAnimation* animation) {
        m_animationSheet = animation;
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

        if(!m_animationSheet )
            return;
        auto* render = m_animationSheet -> getAnimationRender();
        if(!render || m_animationSheet -> getFramesCount() == 0)
            return;

        auto curFrameIndex = m_animationSheet -> getCurrentFrame();
        auto* animation = m_animationSheet -> getAnimation();
        const auto& rect = animation -> frames[curFrameIndex];


        auto contentSize = ImGui::GetWindowSize();

        robot2D::vec2f coof = {
                rect.width / (contentSize.x / 2.F),
                rect.height / (contentSize.y / 2.F)
        };

        robot2D::vec2f imageSize = { rect.width * 2.F, rect.height * 2.F};
        ImGui::SetCursorPos({(contentSize.x - imageSize.x) / 2.F, (contentSize.y - imageSize.y) / 2.F});

        robot2D::DrawAnimatedImage(*render, imageSize);
    }
}