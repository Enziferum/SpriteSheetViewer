#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerScene.hpp>
#include <viewer/macro.hpp>



#include <viewer/panels/MenuPanel.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/panels/ScenePanel.hpp>
#include <viewer/panels/AnimationPanel.hpp>

#include <GLFW/glfw3.h>
#include <filesystem>

namespace viewer {
    robot2D::Color selectColor = robot2D::Color::Green;

    enum class KeyAction {
        FlipLeft,
        FlipRight,
        DeleteFrame,
        Undo,
        Redo,
        Transparent
    };

    static std::unordered_map<KeyAction, robot2D::Key> m_inputMap = {
            {KeyAction::FlipLeft, robot2D::Key::A},
            {KeyAction::FlipRight, robot2D::Key::D},
            {KeyAction::DeleteFrame, robot2D::Key::DEL},
            {KeyAction::Undo, robot2D::Key::Z},
            {KeyAction::Redo, robot2D::Key::R},
            {KeyAction::Transparent, robot2D::Key::T},
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

        m_eventBinder.bindEvent(robot2D::Event::Resized, [this](const robot2D::Event& event) {
            RB_INFO("New Size = {0} and {1}", event.size.widht, event.size.heigth);
            m_window -> resize({event.size.widht, event.size.heigth});
            m_camera2D.resetViewport({event.size.widht, event.size.heigth});
            m_frameBuffer -> Resize({event.size.widht, event.size.heigth});
        });

        m_eventBinder.bindEvent(robot2D::Event::MouseMoved, [this](const robot2D::Event& event) {
            if(m_leftMousePressed) {
                robot2D::vec2f movePos{event.move.x, event.move.y};

                auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
                movePos -= bounds;
                movePos = m_camera2D.mapPixelToCoords(movePos, m_frameBuffer);

                auto pos = m_selectCollider.getPosition();
                m_selectCollider.setSize({movePos.x - pos.x, movePos.y - pos.y});
                m_Manager.setCollider(m_selectCollider.getRect());
            }
        });

        m_eventBinder.bindEvent(robot2D::Event::MousePressed, BIND_CLASS_FN(onMousePressed));
        m_eventBinder.bindEvent(robot2D::Event::MouseReleased, BIND_CLASS_FN(onMouseReleased));
        m_eventBinder.bindEvent(robot2D::Event::KeyPressed, BIND_CLASS_FN(onKeyboardPressed));

        // TODO(a.raag): make as window callback in future
        auto windowHandle = static_cast<GLFWwindow*>(m_window -> getRaw());
        glfwSetDropCallback(windowHandle, dropCallback);

        dragObserver.addObserver([](const std::string& path, DragObserver::FileType fileType) {
            //TODO(a.raag): loading file async
        });
    }

    void ViewerScene::setup(robot2D::RenderWindow* window) {
        m_window = window;

        m_panelManager.addPanel<viewer::MenuPanel>(m_messageBus);
        m_panelManager.addPanel<viewer::ViewerPanel>();
        m_panelManager.addPanel<viewer::AnimationPanel>(m_messageBus, m_messageDispatcher);
        auto winSize = m_window -> getSize();
        m_camera2D.resetViewport(winSize.as<float>());

        m_View.setup(winSize.as<int>(), &m_camera2D);
        m_frameBuffer = m_View.getFrameBuffer();

        m_panelManager.addPanel<viewer::ScenePanel>(m_messageBus, m_camera2D);
        m_panelManager.getPanel<ScenePanel>().setFramebuffer(m_frameBuffer);
        m_panelManager.getPanel<AnimationPanel>().setAnimation(m_View.getAnimation());
        m_Manager.setup(this);

        m_camera2D.setRenderTarget(m_window);
        m_window -> setMaximazed(true);

        setupResources();
        setupBindings();
    }

    void ViewerScene::handleEvents(const robot2D::Event& event) {
        m_panelManager.handleEvents(event);
        m_eventBinder.handleEvents(event);
        auto& panel = m_panelManager.getPanel<ScenePanel>();
        if(panel.isMouseOver())
            m_camera2D.handleEvents(event);
    }

    void ViewerScene::update(float dt) {
        m_View.update(dt);
        m_panelManager.update(dt);
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

    void ViewerScene::onMousePressed(const robot2D::Event& event) {
        robot2D::vec2i convertedPoint { event.mouse.x, event.mouse.y };
        auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
        convertedPoint -= bounds.as<int>();
        auto formatted = m_camera2D.mapPixelToCoords(convertedPoint.as<float>(), m_frameBuffer);
        convertedPoint = formatted.as<int>();

        std::pair<bool, int> collisionPair = {false, -1};

        if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
            collisionPair = m_Manager.getCollisionPair(convertedPoint.as<float>());
        }

        if(collisionPair.first && collisionPair.second != -1) {
            auto& collider = m_Manager.getCollider(collisionPair.second);
            m_selectCollider.setRect(collider.getRect());

            if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
                m_leftMousePressed = true;
                collider.showMovePoints = true;
            }
            else if(event.mouse.btn == robot2D::Mouse::MouseRight) {
                collider.borderColor = robot2D::Color::Magenta;
            }
        }
        else {
            if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
                m_leftMousePressed = true;
                m_selectCollider.setPosition({convertedPoint.x, convertedPoint.y});
            }
        }
    }

    void ViewerScene::onMouseReleased(const robot2D::Event& event) {
        if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
            auto rect = m_selectCollider.getRect();
            if(m_View.insideView({rect.lx, rect.ly, rect.width, rect.height}))
                m_Manager.cutFrames(m_selectCollider.getRect(), m_View.getPosition());
        }

        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            m_selectCollider = {};
            m_leftMousePressed = false;
        }
    }

    void ViewerScene::onKeyboardPressed(const robot2D::Event& event) {

        if(event.key.code == m_inputMap[KeyAction::FlipLeft]) {
            m_View.flipAnimation(false);
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::FlipRight]) {
            m_View.flipAnimation(true);
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::DeleteFrame]) {
            m_Manager.deleteFrame();
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::Undo]) {
            m_Manager.undo();
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::Redo]) {
            m_Manager.redo();
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::Transparent]) {
            auto sz = m_window -> getSize();
            m_View.processImage(m_window -> getMousePos(), sz.as<float>());
            return;
        }
    }

    void ViewerScene::updateAnimation(ViewerAnimation* animation) {
        m_currentAnimation = animation;
        auto& viewerPanel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = viewerPanel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(animation -> getAnimation());
    }

    void ViewerScene::onLoadImage(robot2D::Image&& image) {
        m_View.onLoadImage(std::move(image));
    }

}
