#include <robot2D/Engine.hpp>
#include <viewer/Viewer.hpp>

#include <stack>
#include <viewer/Quad.hpp>
#include <viewer/Collider.hpp>
#include <viewer/utils.hpp>
#include <viewer/Camera2D.hpp>

#include <numeric>
#include <viewer/SpriteCutter.hpp>

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

struct EventBuffer {
    friend std::ostream& operator<<(std::ostream& os, const EventBuffer& eventBuffer);
    std::vector<robot2D::Event> m_events;
};

std::string keyToString(const robot2D::Key& key) {
    switch (key) {
        case robot2D::Key::R:
            return "R";
        case robot2D::Key::S:
            return "S";
        case robot2D::Key::LEFT_CONTROL:
            return "LEFT_CONTROL";
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& os, const EventBuffer& eventBuffer) {
    os << "EventBuffer contains events: " << "\n";
    for(const auto& event: eventBuffer.m_events) {
        switch(event.type) {
            case robot2D::Event::KeyPressed: {
                os << "Event: KeyPressed, Key: " << keyToString(event.key.code) << "\n";
                break;
            }

            default:
                break;
        }
    }
    return os;
}

class DemoCheck: public robot2D::Application {
public:
    EventBuffer m_eventBuffer;

    ~DemoCheck() override = default;

    void setup() override {
        q.position = {200, 200};
        q.size = {200, 200};
        q.color = robot2D::Color::Yellow;
    }

    void handleEvents(const robot2D::Event& event) override {
        if(event.type == robot2D::Event::MouseMoved) {
            if(robot2D::Window::isMousePressed(robot2D::Mouse::MouseMiddle)) {

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

        m_eventBuffer.m_events.push_back(event);
        std::cout << m_eventBuffer << "\n";
    }

    void update(float deltaTime) override {
        if(robot2D::Window::isKeyboardPressed(robot2D::Key::Q))
            std::cout << m_eventBuffer << "\n";
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

class ISandboxCase {
public:

    virtual ~ISandboxCase() = 0;
    virtual void setup(robot2D::RenderWindow* window) = 0;
    virtual void handleEvents(const robot2D::Event& event){}
    virtual void render() = 0;
protected:
    robot2D::RenderWindow* m_window;
};

ISandboxCase::~ISandboxCase() {}

class Sandbox: public robot2D::Application {
public:
    Sandbox();
    ~Sandbox() override = default;

    template<typename T, typename ... Args>
    void registerCase(Args&& ... args) {
        static_assert(std::is_base_of<ISandboxCase, T>::value && "Custom class must be inherit of ISandboxCase");
        m_sandboxCase = std::make_unique<T>(std::forward<Args>(args)...);
        assert(m_sandboxCase != nullptr && "error to create custom Sandbox's case");
    }

    void setup() override;
    void handleEvents(const robot2D::Event &event) override;
    void render() override;
private:
    std::unique_ptr<ISandboxCase> m_sandboxCase;
};

Sandbox::Sandbox() {}


void Sandbox::setup() {
    assert(m_sandboxCase && "Register sandbox's case before using");
    m_sandboxCase -> setup(m_window);
}

void Sandbox::handleEvents(const robot2D::Event& event) {
    m_sandboxCase -> handleEvents(event);
}

void Sandbox::render() {
    m_window -> clear(robot2D::Color::White);
    m_sandboxCase -> render();
    m_window -> display();
}


class SpriteSheetClipper: public ISandboxCase {
public:
    SpriteSheetClipper() = default;
    ~SpriteSheetClipper() override;

    void setup(robot2D::RenderWindow* window) override;
    void handleEvents(const robot2D::Event &event) override;
    void render() override;
private:
    robot2D::Texture m_texture;
    viewer::Collider m_movingQuad;
    std::vector<viewer::Collider> m_colliders;
    bool m_leftBtnPressed{false};
    viewer::Camera2D m_camera;
};

SpriteSheetClipper::~SpriteSheetClipper() noexcept = default;

#define RB2D_THROW(message, ...)

void applyImageMask(robot2D::Image& image, robot2D::Color imageMask) {
    auto colorFormat = image.getColorFormat();
    assert(colorFormat == robot2D::ImageColorFormat::RGBA && "Avalable apply image mask only to RGBA color format");
    auto* buffer = image.getBuffer();
    assert(buffer != nullptr && "Load image before apply mask");
    const auto& size = image.getSize();

    for(int i = 0; i < static_cast<int>(size.x * size.y * 4); i += 4) {
        if(buffer[i] == imageMask.red && buffer[i + 1] == imageMask.green && buffer[i + 2] == imageMask.blue) {
            buffer[i + 3] = 0;
        }
    }
}

// tools
// 1. Dynamic asset load
// 2. THROW if can't load smth
// 3. Dynamic cursor position;
// 4. color detector;


void SpriteSheetClipper::setup(robot2D::RenderWindow* window) {
    m_window = window;
    std::string imagePath = "res/RICO.PNG";

    robot2D::Image image;
    if(!image.loadFromFile(imagePath)) {
        RB2D_THROW("Can't load image by path {0}", imagePath);
        return;
    }

    robot2D::Color colorMask = {51, 51, 51};
    applyImageMask(image, colorMask);

    m_camera.resetViewport({1280, 920});

    m_texture.create(image);
}


class PixelBuffer {
    using byte = unsigned char;

    struct Iterator {
        Iterator(byte* b): ptr{b}{}
        ~Iterator() = default;

        bool operator ==(const Iterator& other) {
            return ptr == other.ptr;
        }

        bool operator !=(const Iterator& other) {
            return  !(*this == other);
        }

        byte& operator*() {
            return *ptr;
        }

        void operator++() {
            ++ptr;
        }
    private:
        byte* ptr;
    };
public:
    PixelBuffer():m_ptr{nullptr}, m_size{0} {}
    PixelBuffer(byte* buffer, std::size_t size, unsigned int channelNum = 4);
    ~PixelBuffer() = default;

    void setBuffer(byte* buffer, std::size_t size, unsigned int channelNum = 4) {
        m_ptr = buffer;
        m_size = size;
        m_channelNum = channelNum;
    }

    Iterator begin() {
        return Iterator{m_ptr};
    }

    Iterator end() {
        return Iterator{m_ptr + m_size};
    }

    byte& operator[](std::size_t index) {
        return m_ptr[index];
    }

    byte& operator()(std::size_t row, std::size_t column) {
        unsigned int index = row * m_size * m_channelNum + column * m_channelNum;
        return m_ptr[index];
    }

    explicit operator bool() {
        return m_ptr && m_size;
    }
private:
    byte* m_ptr;
    std::size_t m_size;
    unsigned int m_channelNum = 4;
};



void SpriteSheetClipper::handleEvents(const robot2D::Event& event) {
    if(event.type == robot2D::Event::MouseMoved) {
        if(m_leftBtnPressed) {
            auto movePos = m_window -> mapPixelToCoords({event.move.x, event.move.y}, m_camera.getCameraView());
            auto pos = m_movingQuad.getPosition();
            m_movingQuad.setSize({
                movePos.x - pos.x,
                movePos.y - pos.y
            });
        }
    }

    if(event.type == robot2D::Event::MousePressed) {
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            auto mousePos = m_window -> mapPixelToCoords({event.mouse.x, event.mouse.y}, m_camera.getCameraView());
            m_leftBtnPressed = true;
            m_movingQuad.setPosition({mousePos.x, mousePos.y});
            auto c = viewer::readPixel({mousePos.x, 920 - mousePos.y});
            m_leftBtnPressed = true;
        }

    }

    if(event.type == robot2D::Event::MouseReleased) {
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            m_leftBtnPressed = false;

            const auto& aabb = m_movingQuad.getRect();
            robot2D::UIntRect clipRegion = {
                    static_cast<unsigned int>(aabb.lx),
                    static_cast<unsigned int>(aabb.ly),
                    static_cast<unsigned int>(aabb.width),
                    static_cast<unsigned int>(aabb.height)
            };

            auto&& cuttedFrames = viewer::SpriteCutter{}.cutFrames(clipRegion, m_texture, {100, 100});

            for(const auto& cut: cuttedFrames) {
                viewer::Collider debugCollider{};
                debugCollider.setRect({cut.lx, cut.ly}, {cut.width, cut.height});
                m_colliders.emplace_back(debugCollider);
            }

            m_movingQuad = {};
        }

    }

    m_camera.handleEvents(event);
    m_camera.update(0, m_window);
}


void SpriteSheetClipper::render() {
    robot2D::Sprite sprite;
    auto& textureSize = m_texture.getSize();
    sprite.setTexture(m_texture, {0, 0, textureSize.x, textureSize.y});
    sprite.setPosition({100, 100});
    m_window -> beforeRender();
    m_window -> setView(m_camera.getCameraView());
    m_window -> draw(sprite);
    m_window -> draw(m_movingQuad);
    for(const auto& obj: m_colliders)
        m_window -> draw(obj);
    m_window -> afterRender();
}





int sandboxRun() {
    robot2D::EngineConfiguration engineConfiguration{};
    engineConfiguration.windowSize = { 1280, 920 };
    engineConfiguration.windowTitle = "SpriteSheetClipper";


    robot2D::robot2DInit();
    std::unique_ptr<Sandbox> sandboxPtr = std::make_unique<Sandbox>();
    sandboxPtr -> registerCase<SpriteSheetClipper>();

    return robot2D::runEngine(std::move(sandboxPtr), std::move(engineConfiguration));
}

int main() {
    robot2D::EngineConfiguration engineConfiguration{};
    engineConfiguration.windowSize = { 1280, 920 };
    engineConfiguration.windowTitle = "SpriteSheet";

    //sandboxRun();

    ROBOT2D_RUN_ENGINE(viewer::Viewer, engineConfiguration)
}