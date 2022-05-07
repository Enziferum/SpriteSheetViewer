#include <robot2D/Core/Clock.hpp>
#include <viewer/Viewer.hpp>

namespace viewer {

    namespace {
        robot2D::Clock frameClock;
        constexpr float timePerFrame = 1.F / 60.F;
        float timeProcessed = 0.F;
    }

    Viewer::Viewer(): m_window({1280, 920}, "SpriteSheetViewer",
                               robot2D::WindowContext::Default), m_scene(m_window) {}


    void Viewer::run() {
        m_gui.init(m_window);
        m_scene.setup();

        frameClock.restart();
        while (m_window.isOpen()) {
            float dt = frameClock.restart().asSeconds();
            timeProcessed += dt;
            while (timeProcessed > timePerFrame) {
                timeProcessed -= timePerFrame;
                handleEvents();
                update(timePerFrame);
            }
            guiRender(dt);
            render();
        }
    }

    void Viewer::handleEvents() {
        robot2D::Event event{};
        while (m_window.pollEvents(event)) {
            if(event.type == robot2D::Event::KeyPressed &&
               event.key.code == robot2D::Key::ESCAPE)
                m_window.close();
            m_gui.handleEvents(event);
            m_scene.handleEvents(event);
        }
    }

    void Viewer::update(float dt) {
        m_scene.update(dt);
    }

    void Viewer::guiRender(float dt) {
        m_gui.update(dt);
    }

    void Viewer::render() {
        m_window.clear(robot2D::Color::Black);
        m_scene.render();
        m_gui.render();
        m_window.display();
    }
}