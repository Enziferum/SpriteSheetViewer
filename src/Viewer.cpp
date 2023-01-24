#include <cassert>
#include <viewer/Viewer.hpp>

namespace viewer {

    Viewer::Viewer():
    m_messageBus{},
    m_messageDispatcher{},
    m_scene{m_messageBus, m_messageDispatcher}{}

    void Viewer::setup() {
        assert(m_window != nullptr && "RenderWindow must be available already.");
        m_gui.setup(*m_window);
        m_scene.setup(m_window);
        m_window -> setVsync(true);
        {
            robot2D::Image iconImage;
            iconImage.loadFromFile("res/logo.png");
            m_window -> setIcon(std::move(iconImage));
        }
    }

    void Viewer::handleEvents(const robot2D::Event& event) {
        m_gui.handleEvents(event);
        m_scene.handleEvents(event);
    }

    void Viewer::handleMessages() {
        robot2D::Message message{};
        while(m_messageBus.pollMessages(message)) {
            m_messageDispatcher.process(message);
        }
    }

    void Viewer::update(float dt) {
        m_scene.update(dt);
    }

    void Viewer::guiUpdate(float dt) {
        m_gui.update(dt);
    }

    void Viewer::render() {
        m_window -> clear(robot2D::Color::White);
        m_scene.render();
        m_gui.render();
        m_window -> display();
    }
}