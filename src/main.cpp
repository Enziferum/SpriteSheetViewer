#include <robot2D/Engine.hpp>
#include <viewer/Viewer.hpp>

int main() {
    robot2D::EngineConfiguration engineConfiguration{};
    engineConfiguration.windowSize = { 1280, 920 };
    engineConfiguration.windowTitle = "SpriteSheetViewer";

    ROBOT2D_RUN_ENGINE(viewer::Viewer, engineConfiguration)
}