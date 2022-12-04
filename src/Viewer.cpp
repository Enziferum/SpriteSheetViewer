#include <cassert>
#include <viewer/Viewer.hpp>

namespace viewer {

    Viewer::Viewer() {}

    void Viewer::setup() {
        assert(m_window != nullptr && "RenderWindow must be available already.");
        m_gui.init(*m_window);
        m_scene.setup(m_window);
    }

    void Viewer::handleEvents(const robot2D::Event& event) {
        m_gui.handleEvents(event);
        m_scene.handleEvents(event);
    }

    void Viewer::update(float dt) {
        m_scene.update(dt);
    }

    void Viewer::guiUpdate(float dt) {
        m_gui.update(dt);
    }

    void Viewer::render() {
        m_window -> clear(robot2D::Color::Black);
        m_scene.render();
        m_gui.render();
        m_window -> display();
    }
}