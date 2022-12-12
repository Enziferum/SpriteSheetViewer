#pragma once

#include <robot2D/Application.hpp>
#include <robot2D/imgui/Gui.hpp>
#include <robot2D/Core/MessageBus.hpp>

#include "ViewerScene.hpp"
#include "MessageDispather.hpp"

namespace viewer {

    class Viewer: public robot2D::Application {
    public:
        Viewer();
        Viewer(const Viewer& other) = delete;
        Viewer& operator=(const Viewer& other) = delete;
        Viewer(Viewer&& other) = delete;
        Viewer& operator=(Viewer&& other) = delete;
        ~Viewer() override = default;

    private:
        void setup() override;
        void handleEvents(const robot2D::Event& event) override;
        void handleMessages() override;
        void update(float dt) override;
        void guiUpdate(float dt) override;
        void render() override;
    private:
        robot2D::MessageBus m_messageBus;
        MessageDispatcher m_messageDispatcher;

        ViewerScene m_scene;
        robot2D::Gui m_gui;
    };
} // namespace viewer