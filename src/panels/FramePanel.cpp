#include <viewer/panels/FramePanel.hpp>
#include <robot2D/imgui/Api.hpp>

namespace viewer {

    FramePanel::FramePanel(): IPanel(typeid(FramePanel)) {}

    void FramePanel::update(float dt) {
        (void)dt;
    }
} // namespace viewer