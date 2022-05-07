#include <robot2D/Engine.hpp>
#include <robot2D/Extra/Gui.hpp>

namespace {
    // ImGui ShowDemo
    bool open = true;
}

class MyApplication: public robot2D::Application {
public:
    MyApplication();
    ~MyApplication() override = default;

    void setup() override;

    void handleEvents(const robot2D::Event& event) override;
    /// Make ImGui Update / Rendering only in guiUpdate method.
    void guiUpdate(float deltaTime) override;
    void render() override;
private:
    ImGui::Gui m_gui;
};

MyApplication::MyApplication(): m_gui{} {}

void MyApplication::setup() {
    m_gui.init(*m_window);
}

void MyApplication::handleEvents(const robot2D::Event& event) {
    m_gui.handleEvents(event);
}

void MyApplication::guiUpdate(float deltaTime) {
    m_gui.update(deltaTime);
    ImGui::ShowDemoWindow(&open);
}

void MyApplication::render() {
    m_window -> clear();
    m_gui.render();
    m_window -> display();
}

#define SIMPLE_MAIN 0
#if SIMPLE_MAIN == 1
    ROBOT2D_MAIN(MyApplication)
#elif SIMPLE_MAIN == 0
int main() {
    robot2D::EngineConfiguration engineConfiguration{
        {1280, 920},
        {"Robot2D + ImGui"}
    };
    ROBOT2D_RUN_ENGINE(MyApplication, engineConfiguration)
}
#endif