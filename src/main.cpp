#include <robot2D/Engine.hpp>
#include <viewer/Viewer.hpp>

#include <stack>
#include <viewer/Quad.hpp>

class ICommand {
public:
    using Ptr = std::shared_ptr<ICommand>;

    ICommand(){}
    virtual ~ICommand() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;
};

class CommandStack {
public:
    CommandStack(): m_commands() {}
    ~CommandStack() = default;

    template<typename T, typename ... Args>
    T* addCommand(Args&& ... args) {
        static_assert(std::is_base_of_v<ICommand, T> && "T must be inherit of ICommand");
        auto command = std::make_shared<T>(std::forward<Args>(args)...);
        if(!command)
            return nullptr;
        m_commands.push(command);
        return (dynamic_cast<T*>(top()));
    }

    void undo() {
        auto command = m_commands.top();
        command -> undo();
    }

    void redo() {
        auto command = m_commands.top();
        command -> undo();
    }

    ICommand::Ptr top() const {
        return m_commands.top();
    }

    void pop() {
        m_commands.pop();
    }

    bool empty() const noexcept {
        return m_commands.empty();
    }

    std::size_t size() const noexcept {
        return m_commands.size();
    }

    void clear() {
        while(!m_commands.empty())
            m_commands.pop();
    }

private:
    std::stack<ICommand::Ptr> m_commands;
    /// save redo Operations
    std::stack<ICommand::Ptr> m_redoCommands;
};



class PaintCommand: public ICommand {
public:
    ~PaintCommand() override;

    void undo() override;
    void redo() override {};
};

void PaintCommand::undo() {

}


class DeleteCommand: public ICommand{
public:
    ~DeleteCommand() override = default;
};



class DemoCheck: public robot2D::Application {
public:
    ~DemoCheck() override = default;

    void setup() override {
        q.position = {200, 200};
        q.size = {200, 200};
        q.color = robot2D::Color::Yellow;
    }

    void handleEvents(const robot2D::Event& event) override {
        if(event.type == robot2D::Event::MouseMoved) {
            if(robot2D::Window::isMousePressed(robot2D::Mouse::MouseLeft)) {

                auto mousePos = m_window -> getMousePos();
                if(lastMousePos == robot2D::vec2f {-1, -1})
                    lastMousePos = mousePos;
                RB_INFO("Mouse POS {0}: {1}", mousePos.x, mousePos.y);

                if(std::abs(mousePos.x - lastMousePos.x) > 1.F
                   || std::abs(mousePos.y - lastMousePos.y) > 1.F) {

                    while (lastMousePos.x < mousePos.x) {
                        ++lastMousePos.x;
                        insertQuad(lastMousePos);
                    }
                    while (lastMousePos.y < mousePos.y) {
                        ++lastMousePos.y;
                        insertQuad(lastMousePos);
                    }
                }
                lastMousePos = mousePos;
                insertQuad(mousePos);
            }
        }


    }

    void update(float deltaTime) override {
        if(robot2D::Window::isKeyboardPressed(robot2D::Key::Q))
            quads.clear();
    }

    void render() override {
        m_window -> clear();
        m_window -> beforeRender();
        for(const auto& quad: quads)
            m_window -> draw(quad);
        m_window -> afterRender();
        m_window -> display();
    }
private:
    void insertQuad(robot2D::vec2f position) {
        viewer::Quad tmp;
        tmp.position = position;
        tmp.size = {1, 1};
        tmp.color = robot2D::Color::Green;
        if(quads.size() < 1500)
            quads.emplace_back(tmp);
    }
private:
    viewer::Quad q;
    std::vector<viewer::Quad> quads;
    robot2D::vec2f lastMousePos = {-1, -1};

    PaintCommand::Ptr m_paintCommand;
    CommandStack m_commandStack;
};


int main() {
    robot2D::EngineConfiguration engineConfiguration{};
    engineConfiguration.windowSize = { 1280, 920 };
    engineConfiguration.windowTitle = "SpriteSheet";

    //
    ROBOT2D_RUN_ENGINE(viewer::Viewer, engineConfiguration);
}