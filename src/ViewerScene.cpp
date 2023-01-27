#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerScene.hpp>
#include <viewer/Macro.hpp>
#include <viewer/Defines.hpp>

#include <viewer/panels/MenuPanel.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/panels/ScenePanel.hpp>
#include <viewer/panels/AnimationPanel.hpp>

#include <GLFW/glfw3.h>
#include <filesystem>

namespace viewer {
    robot2D::Color selectColor = robot2D::Color::Green;

    struct KeyInput {
        //robot2D::Key getKey(const Action& action) const;
    private:
    };

    enum class KeyAction {
        FlipLeft,
        FlipRight,
        DeleteFrame,
        Undo,
        Redo,
        Transparent,
        CutMode
    };


    class InputManager {
    public:
        InputManager();
        ~InputManager();


    private:
        EventBinder& m_eventBinder;
        std::unordered_map<KeyAction, robot2D::Key> m_inputMap;
    };


    static std::unordered_map<KeyAction, robot2D::Key> m_inputMap = {
            {KeyAction::FlipLeft, robot2D::Key::A},
            {KeyAction::FlipRight, robot2D::Key::D},
            {KeyAction::DeleteFrame, robot2D::Key::DEL},
            {KeyAction::Undo, robot2D::Key::Z},
            {KeyAction::Redo, robot2D::Key::R},
            {KeyAction::Transparent, robot2D::Key::T},
            {KeyAction::CutMode, robot2D::Key::M},
    };

    namespace fs = std::filesystem;

    struct DragObserver {
        enum class FileType {
            Png, Xml
        };

        using DragObserverCallback = std::function<void(const std::string&, FileType)>;

        void notity(const std::string& path, FileType fileType) const {
            if(m_callback)
                m_callback(path, fileType);
        }

        void addObserver(DragObserverCallback&& callback) {
            m_callback = std::move(callback);
        }

        DragObserverCallback m_callback;
    } dragObserver;

    void dropCallback(GLFWwindow* window, int path_count, const char* paths[]) {
        for(int i = 0; i < path_count; ++i) {
            auto path = fs::path{paths[i]};
            if(is_regular_file(path)) {

                if(path.extension() == ".png")
                    dragObserver.notity(path.string(), DragObserver::FileType::Png);

                if(path.extension() == ".xml")
                    dragObserver.notity(path.string(), DragObserver::FileType::Xml);
            }
        }
    }



    ViewerScene::ViewerScene(robot2D::MessageBus& messageBus, MessageDispatcher& dispatcher):
    m_window{nullptr},
    m_messageBus{messageBus},
    m_messageDispatcher{dispatcher},
    m_Manager(messageBus, dispatcher)
    {}

    void ViewerScene::setupResources() {
        auto* sheetAnimation = m_View.getAnimation();
        auto& viewer = m_panelManager.getPanel<ViewerPanel>();
        viewer.setSpriteSheetAnimation(sheetAnimation);
        auto& animation = m_panelManager.getPanel<AnimationPanel>();
        animation.setAnimation(sheetAnimation);
    }

    void ViewerScene::setupBindings() {
        /*
        auto& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

        cursor.create(robot2D::CursorType::ResizeLeftRight);
        m_window -> setCursor(cursor);
        */

        bool bindResult = false;
        bindResult = m_eventBinder.bindEvent<robot2D::Event::SizeEvent>(robot2D::Event::Resized,
                                                                        [this](const auto& event) {
            RB_INFO("New Size = {0} and {1}", event.widht, event.heigth);
            robot2D::vec2f newSize = {event.widht, event.heigth};
            m_window -> resize(newSize.as<int>());
            m_camera2D.resetViewport(newSize);
            m_frameBuffer -> Resize(newSize.as<unsigned int>());
        });

        if(!bindResult) {
            RB_CRITICAL("Can't bind SizeEvent callback");
            THROW("Can't bind SizeEvent callback");
        }

        bindResult = m_eventBinder.bindEvent<robot2D::Event::MouseMoveEvent>(robot2D::Event::MouseMoved,
                                                                BIND_CLASS_FN(onMouseMoved));

        if(!bindResult) {
            RB_CRITICAL("Can't bind MouseMove callback");
            THROW("Can't bind MouseMove callback");
        }

        bindResult = m_eventBinder.bindEvent<robot2D::Event::MouseButtonEvent>(robot2D::Event::MousePressed,
                                                                  BIND_CLASS_FN(onMousePressed));

        if(!bindResult) {
            RB_CRITICAL("Can't bind MouseButtonEvent(Pressed) callback");
            THROW("Can't bind MouseButtonEvent(Pressed) callback");
        }

        bindResult = m_eventBinder.bindEvent<robot2D::Event::MouseButtonEvent>(robot2D::Event::MouseReleased,
                                                                  BIND_CLASS_FN(onMouseReleased));

        if(!bindResult) {
            RB_CRITICAL("Can't bind MouseButtonEvent(Released) callback");
            THROW("Can't bind MouseButtonEvent(Released) callback");
        }

        bindResult = m_eventBinder.bindEvent<robot2D::Event::KeyboardEvent>(robot2D::Event::KeyPressed,
                                                                BIND_CLASS_FN(onKeyboardPressed));

        if(!bindResult) {
            RB_CRITICAL("Can't bind KeyboardEvent callback");
            THROW("Can't bind KeyboardEvent callback");
        }


        // TODO(a.raag): make as window callback in future
        auto windowHandle = static_cast<GLFWwindow*>(m_window -> getRaw());
        glfwSetDropCallback(windowHandle, dropCallback);

        dragObserver.addObserver([](const std::string& path, DragObserver::FileType fileType) {
            //TODO(a.raag): loading file async
        });
    }

    void ViewerScene::setup(robot2D::RenderWindow* window) {
        m_window = window;
        m_Manager.setup(this);

        m_panelManager.addPanel<viewer::MenuPanel>(m_messageBus);
        m_panelManager.addPanel<viewer::ViewerPanel>();
        m_panelManager.addPanel<viewer::ScenePanel>(m_messageBus, m_messageDispatcher, m_camera2D);
        m_panelManager.addPanel<viewer::AnimationPanel>(m_messageBus, m_messageDispatcher);

        auto winSize = m_window -> getSize();
        m_camera2D.resetViewport(winSize.as<float>());

        m_View.setup(winSize.as<int>(), &m_camera2D);
        m_frameBuffer = m_View.getFrameBuffer();

        m_panelManager.getPanel<ScenePanel>().setFramebuffer(m_frameBuffer);
        m_panelManager.getPanel<AnimationPanel>().setAnimation(m_View.getAnimation());


        m_camera2D.setRenderTarget(m_window);
        m_window -> setMaximazed(true);

        setupResources();
        setupBindings();
    }

    void ViewerScene::handleEvents(const robot2D::Event& event) {
        m_panelManager.handleEvents(event);
        m_eventBinder.handleEvents(event);
        if(!m_panelManager.isMouseIsOver())
            m_camera2D.handleEvents(event);
    }

    void ViewerScene::update(float dt) {
        m_View.update(dt);
        m_panelManager.update(dt);
        if(!m_panelManager.isMouseIsOver())
            m_camera2D.update(dt, m_window);
    }

    void ViewerScene::render() {
        m_View.beforeRender();
        m_window -> draw(m_View);
        if(m_currentAnimation)
            m_window -> draw(*m_currentAnimation);
        if(m_leftMousePressed)
            m_window -> draw(m_selectCollider);
        m_window -> afterRender();
        m_panelManager.render();
        m_View.afterRender();
    }

    void ViewerScene::onMouseMoved(const robot2D::Event::MouseMoveEvent& event) {
        if(m_leftMousePressed && !m_panelManager.isMouseIsOver()) {
            robot2D::vec2f movePos{event.x, event.y};

            auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
            movePos -= bounds;
            movePos = m_camera2D.mapPixelToCoords(movePos, m_frameBuffer);

            auto pos = m_selectCollider.getPosition();
            m_selectCollider.setSize({movePos.x - pos.x, movePos.y - pos.y});
            m_Manager.setCollider(m_selectCollider.getRect());
        }
    }

    void ViewerScene::onMousePressed(const robot2D::Event::MouseButtonEvent& event) {
        if(m_panelManager.isMouseIsOver())
            return;

        robot2D::vec2i convertedPoint { event.x, event.y };
        auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
        convertedPoint -= bounds.as<int>();
        auto formatted = m_camera2D.mapPixelToCoords(convertedPoint.as<float>(), m_frameBuffer);
        convertedPoint = formatted.as<int>();

        std::pair<bool, int> collisionPair = { false, NO_INDEX };

        if(event.btn != robot2D::Mouse::MouseMiddle) {
            collisionPair = m_Manager.getCollisionPair(convertedPoint.as<float>());
        }

        if(collisionPair.first && collisionPair.second != -1) {
            auto& collider = m_Manager.getCollider(collisionPair.second);
            m_selectCollider.setRect(collider.getRect());

            if(event.btn == robot2D::Mouse::MouseLeft) {
                if(collider.state != Collider::State::Selected) {
                    collider.showMovePoints = true;
                }
            }
            else if(event.btn == robot2D::Mouse::MouseRight) {
                switch(collider.state) {
                    default:
                        break;
                    case Collider::State::Default:
                        collider.state = Collider::State::Selected;
                        collider.borderColor = robot2D::Color::Magenta;
                        break;
                    case Collider::State::Selected:
                        collider.state = Collider::State::Default;
                        collider.borderColor = robot2D::Color::Green;
                        break;
                }
            }
        }
        else {
            if(event.btn != robot2D::Mouse::MouseMiddle) {
                m_leftMousePressed = true;
                m_selectCollider.setPosition(convertedPoint.as<float>());
            }
        }
    }

    void ViewerScene::onMouseReleased(const robot2D::Event::MouseButtonEvent& event) {
        if(m_panelManager.isMouseIsOver())
            return;

        if(event.btn != robot2D::Mouse::MouseMiddle) {
            auto rect = m_selectCollider.getRect();
            if(m_View.insideView(rect.as<int>()))
                m_Manager.processFrames(
                        m_selectCollider.getRect(),
                        m_View.getPosition(),
                        m_View.getImage(m_Manager.getCurrentTab())
                );
        }

        if(event.btn == robot2D::Mouse::MouseLeft) {
            m_selectCollider = {};
            m_leftMousePressed = false;
        }
    }

    void ViewerScene::onKeyboardPressed(const robot2D::Event::KeyboardEvent& event) {
        if(m_panelManager.isMouseIsOver())
            return;

        if(event.code == m_inputMap[KeyAction::FlipLeft]) {
            m_View.flipAnimation(false);
            return;
        }

        if(event.code == m_inputMap[KeyAction::FlipRight]) {
            m_View.flipAnimation(true);
            return;
        }

        if(event.code == m_inputMap[KeyAction::DeleteFrame]) {
            m_Manager.deleteFrame();
            return;
        }

        if(event.code == m_inputMap[KeyAction::Undo]) {
            m_Manager.undo();
            return;
        }

        if(event.code == m_inputMap[KeyAction::Redo]) {
            m_Manager.redo();
            return;
        }

        if(event.code == m_inputMap[KeyAction::Transparent]) {
            auto sz = m_window -> getSize();
            auto mousePos = m_window -> getMousePos();

            auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
            mousePos -= bounds;
            mousePos = m_camera2D.mapPixelToCoords(mousePos, m_frameBuffer);

            if(m_View.insideView( { mousePos.as<int>(), {1, 1} }))
                m_View.processImage(mousePos, sz.as<float>());
            return;
        }

        if(event.code == m_inputMap[KeyAction::CutMode]) {
            m_Manager.setCutMode();
            return;
        }
    }


    void ViewerScene::updateView(std::size_t tabIndex, ViewerAnimation* animation) {
        m_currentAnimation = animation;
        auto& viewerPanel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = viewerPanel.getSpriteSheetAnimation();
        if(sheet) {
            sheet -> reset();
            if(animation)
                sheet -> setAnimation(&animation -> getAnimation());
            else
                sheet -> setAnimation(nullptr);
        }
    }

    void ViewerScene::onLoadImage(robot2D::Image&& image) {
        m_View.onLoadImage(std::move(image));
    }

    std::pair<bool, robot2D::vec2f>
    ViewerScene::onLoadAnimation(robot2D::Image&& image) {
        return m_View.onLoadAnimation(std::move(image));
    }

    void ViewerScene::resetNames(const std::vector<std::string>& names) {
        m_panelManager.getPanel<AnimationPanel>().resetNames(names);
    }
}
