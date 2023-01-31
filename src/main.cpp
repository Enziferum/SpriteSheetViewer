#include <robot2D/Engine.hpp>
#include <viewer/Viewer.hpp>
#include <profiler/Profiler.hpp>

int main() {
    robot2D::EngineConfiguration engineConfiguration{};
    engineConfiguration.windowSize = { 1280, 920 };
    engineConfiguration.windowTitle = "SpriteSheetViewer";

    PROFILE_BEGIN("Viewer", "profilerResult.json")
    robot2D::robot2DInit();
    viewer::Viewer::Ptr myApplication = std::make_unique<viewer::Viewer>();
    int result = robot2D::runEngine(std::move(myApplication), std::move(engineConfiguration));
    PROFILE_END()
    return result;
}