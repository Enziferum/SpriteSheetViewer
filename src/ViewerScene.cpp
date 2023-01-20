#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerScene.hpp>
#include <viewer/AnimationIO.hpp>

#include <viewer/panels/MenuPanel.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/panels/ScenePanel.hpp>
#include <viewer/panels/AnimationPanel.hpp>

#include <viewer/macro.hpp>
#include <viewer/utils.hpp>
#include <viewer/SpriteCutter.hpp>

#include <GLFW/glfw3.h>
#include <filesystem>

namespace viewer {

    namespace {
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
    }

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
        viewer.setSpriteSheetAnimation(&sheetAnimation);
        auto& animation = m_panelManager.getPanel<AnimationPanel>();
        animation.setAnimation(&sheetAnimation);
    }

    void ViewerScene::setupBindings() {
//        auto& io = ImGui::GetIO();
//        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
//
//        cursor.create(robot2D::CursorType::ResizeLeftRight);
//        m_window -> setCursor(cursor);

        m_eventBinder.bindEvent(robot2D::Event::Resized, [this](const robot2D::Event& event) {
            RB_INFO("New Size = {0} and {1}", event.size.widht, event.size.heigth);
            m_window -> resize({event.size.widht, event.size.heigth});
  //          m_camera2D.resetViewport({event.size.widht, event.size.heigth});
    //        m_frameBuffer -> Resize({event.size.widht, event.size.heigth});
        });

        m_eventBinder.bindEvent(robot2D::Event::MouseMoved, [this](const robot2D::Event& event) {
            if(m_leftMousePressed) {
                robot2D::vec2f movePos{event.move.x, event.move.y};

                auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
                movePos -= bounds;
                movePos = m_camera2D.mapPixelToCoords(movePos, m_frameBuffer);

                movingAABB.width = movePos.x - movingAABB.lx;
                movingAABB.height = movePos.y - movingAABB.ly;

                if(updateIndex >= 0)
                    m_animations[m_currentAnimation][updateIndex].setRect(movingAABB);
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

        m_panelManager.addPanel<viewer::ScenePanel>(m_messageBus, m_camera2D);
        m_panelManager.getPanel<ScenePanel>().setFramebuffer(m_frameBuffer);
        setupResources();
        setupBindings();

        m_Manager.setupMessages();

        m_camera2D.setRenderTarget(m_window);

        if(!m_sceneGrid.load())
            return;

        m_window -> setMaximazed(true);
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
        m_window -> draw(m_View);
    }


    void ViewerScene::onMousePressed(const robot2D::Event& event) {
//        if(m_panelManager.isMouseIsOver())
//            return;

        robot2D::vec2i convertedPoint { event.mouse.x, event.mouse.y };
        auto bounds = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
        convertedPoint -= bounds.as<int>();
        auto formatted = m_camera2D.mapPixelToCoords(convertedPoint.as<float>(), m_frameBuffer);
        convertedPoint = formatted.as<int>();


        std::pair<bool, int> collisionPair = {false, -1};

        if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
            collisionPair = m_animations[m_currentAnimation].contains(convertedPoint.as<float>());
        }

        updateIndex = collisionPair.second;
        if(collisionPair.first && collisionPair.second != -1) {
            movingAABB = m_animations[m_currentAnimation][collisionPair.second].getRect();
            if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
                m_leftMousePressed = true;
                m_animations[m_currentAnimation][collisionPair.second].showMovePoints = true;
            }
            else if(event.mouse.btn == robot2D::Mouse::MouseRight) {
                m_animations[m_currentAnimation][collisionPair.second].borderColor = robot2D::Color::Magenta;
            }
        }
        else {
            if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
                m_leftMousePressed = true;
                movingAABB.lx = convertedPoint.x;
                movingAABB.ly = convertedPoint.y;
            }
        }
    }

    void ViewerScene::onMouseReleased(const robot2D::Event& event) {
//        if(m_panelManager.isMouseIsOver())
//            return;

        if(updateIndex == -1) {
            if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
                auto dd = viewer::Collider{};
                dd.setRect(movingAABB);
                if(dd.notZero() && dd.intersects(m_animatedSprite.getGlobalBounds())) {
                    auto&& frames = SpriteCutter{}.cutFrames(
                            {movingAABB.lx, movingAABB.ly, movingAABB.width, movingAABB.height},
                            const_cast<robot2D::Texture &>(*m_animatedSprite.getTexture()),
                            m_animatedSprite.getPosition()
                    );

                    frames.erase(
                            std::unique(frames.begin(), frames.end()),
                            frames.end());
                    std::sort(frames.begin(), frames.end());

                    for(const auto& frame: frames) {
                        dd.setRect({frame.lx, frame.ly, frame.width, frame.height});
                        m_commandStack.addCommand<AddFrameCommand>(m_animations[m_currentAnimation], dd);
                        m_animations[m_currentAnimation].addFrame(dd, m_animatedSprite.getPosition());
                    }
                }
            }
        } else {
            m_animations[m_currentAnimation][updateIndex].setRect(movingAABB);
            m_animations[m_currentAnimation][updateIndex].showMovePoints = false;
        }

        m_leftMousePressed = false;
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            movingAABB = {};
            updateIndex = -1;
        }
    }

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

    void ViewerScene::onKeyboardPressed(const robot2D::Event& event) {

        if(event.key.code == m_inputMap[KeyAction::FlipLeft]) {
            sheetAnimation.reset();
            sheetAnimation.setFlip(false);
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::FlipRight]) {
            sheetAnimation.reset();
            sheetAnimation.setFlip(true);
            return;
        }

        if(event.key.code == m_inputMap[KeyAction::DeleteFrame]) {

            m_Manager.deleteFrame();

//            if(updateIndex != -1) {
//                auto frame = m_animations[m_currentAnimation][updateIndex];
//                m_animations[m_currentAnimation].eraseFrame(updateIndex);
//
//                frame.borderColor = robot2D::Color::Green;
//                m_commandStack.addCommand<DeleteFrameCommand>(
//                        m_animations[m_currentAnimation],
//                        frame,
//                        updateIndex
//                );
//
//                updateIndex = -1;
//                movingAABB = {};
//                return;
//            }
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
            m_View.processImage();

            auto mousePos = m_camera2D.mapPixelToCoords(m_window -> getMousePos(), m_frameBuffer);
            auto&& maskColor = readPixel({mousePos.x, m_window -> getSize().y - mousePos.y});
            robot2D::Image image{};
            image.create(m_texture.getSize(), m_texture.getPixels(), robot2D::ImageColorFormat::RGBA);
            applyImageMask(image, maskColor);
            m_texture.create(image);
            return;
        }
    }


}
