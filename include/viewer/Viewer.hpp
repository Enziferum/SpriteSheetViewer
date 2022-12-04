#pragma once

#include <robot2D/Application.hpp>
#include <robot2D/Extra/Gui.hpp>

#include "ViewerScene.hpp"

namespace viewer {

    class Viewer: public robot2D::Application {
    public:
        Viewer();
        ~Viewer() override = default;

    private:
        void setup() override;

        void handleEvents(const robot2D::Event& event) override;
        void update(float dt) override;
        void guiUpdate(float dt) override;
        void render() override;
    private:
        ViewerScene m_scene;
        ImGui::Gui m_gui;
    };
}