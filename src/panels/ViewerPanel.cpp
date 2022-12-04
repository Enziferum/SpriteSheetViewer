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

        const float min_value = 1.f;
        const float max_value = 100.f;
        if(!m_animation )
            return;
        auto sprite = m_animation -> getSprite();

        if(!sprite)
            return;

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
}