#include <robot2D/Util/Logger.hpp>

#include <robot2D/Extra/Api.hpp>
#include <viewer/panels/ViewerPanel.hpp>

#include <tuple>

namespace viewer {

    template<typename F,
            typename = std::enable_if_t<std::is_invocable_v<F>>>
    struct Defer {
        Defer(F&& func):
            m_func{std::move(func)}{}

        ~Defer() {
            try{
                if(m_func)
                    m_func();
            }
            catch (...) {}
        }

        F m_func;
    };

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

        ImGui::Begin("Viewer");
        Defer defer{&ImGui::End};

        m_isMouseOver = ImGui::IsWindowFocused() || ImGui::IsWindowHovered();

        if(!m_animation )
            return;
        auto* render = m_animation -> getAnimationRender();
        if(!render)
            return;

        auto contentSize = ImGui::GetContentRegionAvail();
        robot2D::vec2f possibleImageSize = { 200, 200 };
        ImGui::AnimatedImage(*render, possibleImageSize);
    }
}