#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Extra/Gui.hpp>
#include "ViewerScene.hpp"

namespace viewer {

    class Viewer {
    public:
        Viewer();
        ~Viewer() = default;

        void run();
    private:
        void handleEvents();
        void update(float dt);
        void guiRender(float dt);
        void render();
    private:
        robot2D::RenderWindow m_window;
        ViewerScene m_scene;
        ImGui::Gui m_gui;
    };
}