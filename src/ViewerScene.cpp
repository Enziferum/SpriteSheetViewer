#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerScene.hpp>
#include <viewer/AnimationIO.hpp>

#include <viewer/panels/MenuPanel.hpp>
#include <viewer/panels/ViewerPanel.hpp>
#include <viewer/panels/ScenePanel.hpp>
#include <viewer/panels/AnimationPanel.hpp>

#include <GLFW/glfw3.h>
#include <filesystem>

#include <imgui/imgui.h>

#include <viewer/macro.hpp>


namespace viewer {

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
    m_messageBus{messageBus},
    m_messageDispatcher{dispatcher},
    m_window{nullptr} {}

    void ViewerScene::setupResources() {
        auto spritePosition = robot2D::vec2f {
                0,
                300.F
        };

        m_texture.loadFromFile("res/animations/ZombieBoss/BossWalk.png");
        m_animatedSprite.setTexture(m_texture);
        m_animatedSprite.setPosition(spritePosition);

        m_sprite = m_animatedSprite;
        sheetAnimation.setAnimationRender( m_animatedSprite);

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
            m_window->resize({event.size.widht, event.size.heigth});
            m_camera2D.resetViewport({event.size.widht, event.size.heigth});
            m_frameBuffer -> Resize({event.size.widht, event.size.heigth});
        });

        m_eventBinder.bindEvent(robot2D::Event::MouseMoved, [this](const robot2D::Event& event) {
            if(startedPressed && !m_panelManager.isMouseIsOver()) {
                robot2D::vec2f movePos{event.move.x, event.move.y};
                auto formatted = m_window -> mapPixelToCoords(movePos.as<int>(), m_camera2D.getCameraView());
                movePos = formatted;

                movingAABB.width = movePos.x - movingAABB.lx;
                movingAABB.height = movePos.y - movingAABB.ly;
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

        m_messageDispatcher.onMessage<AddAnimationMessage>(MessageID::AddAnimation,
                                                           BIND_CLASS_FN(onAddAnimation));

        m_messageDispatcher.onMessage<SwitchAnimationMessage>(MessageID::SwitchAnimation,
                                                           BIND_CLASS_FN(onSwitchAnimation));


        m_messageDispatcher.onMessage<DeleteAnimationMessage>(MessageID::DeleteAnimation,
                                                              BIND_CLASS_FN(onDeleteAnimation));
    }

    void ViewerScene::setup(robot2D::RenderWindow* window) {
        m_window = window;

        m_panelManager.addPanel<viewer::MenuPanel>();
        m_panelManager.addPanel<viewer::ViewerPanel>();
        m_panelManager.addPanel<viewer::AnimationPanel>(m_messageBus);
        auto winSize = m_window -> getSize();
        m_camera2D.resetViewport(winSize.as<float>());


        robot2D::FrameBufferSpecification frameBufferSpecification;
        frameBufferSpecification.attachments =  {
                robot2D::FrameBufferTextureFormat::RGBA8
        };
        frameBufferSpecification.size = winSize.as<int>();
        m_frameBuffer = robot2D::FrameBuffer::Create(frameBufferSpecification);

        m_panelManager.addPanel<viewer::ScenePanel>(m_camera2D);
        m_panelManager.getPanel<ScenePanel>().setFramebuffer(m_frameBuffer);
        setupResources();
        setupBindings();

        m_camera2D.setRenderTarget(m_window);

        m_window -> setMaximazed(true);
    }


    void ViewerScene::handleEvents(const robot2D::Event& event) {
        m_panelManager.handleEvents(event);
        m_eventBinder.handleEvents(event);
        m_camera2D.handleEvents(event);
    }

    void ViewerScene::update(float dt) {
        sheetAnimation.update(dt);
        m_panelManager.update(dt);
        m_camera2D.update(dt, m_window);
    }

    void ViewerScene::render() {
        m_frameBuffer -> Bind();
        m_window -> clear(robot2D::Color::White);
        m_window -> beforeRender();
        m_window -> setView(m_camera2D.getCameraView());

        m_window -> draw(m_sprite);
        if(m_currentAnimation >= 0)
            m_window -> draw(m_animations[m_currentAnimation]);

        if(startedPressed) {
            viewer::DebugCollider debugCollider;
            debugCollider.aabb = movingAABB;
            debugCollider.borderColor = selectColor;
            m_window -> draw(debugCollider);
        }

        m_window -> afterRender();
        m_panelManager.render();
        m_frameBuffer -> unBind();
    }

    void ViewerScene::onMousePressed(const robot2D::Event& event) {
        if(m_panelManager.isMouseIsOver())
            return;

        robot2D::vec2i convertedPoint { event.mouse.x, event.mouse.y };
        auto formatted = m_window -> mapPixelToCoords(convertedPoint, m_camera2D.getCameraView());
        formatted = m_panelManager.getPanel<ScenePanel>().getPanelBounds();
        convertedPoint = formatted.as<int>();

        RB_INFO("Formatted Point by ViewerScene {0}: {1}", formatted.x, formatted.y);

        std::pair<bool, int> collisionPair = {false, -1};

        if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
            collisionPair = m_animations[m_currentAnimation].contains(convertedPoint.as<float>());
        }

        updateAABBit = collisionPair.second;
        if(collisionPair.first && collisionPair.second != -1) {
            movingAABB = m_animations[m_currentAnimation][collisionPair.second].aabb;
            if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
                movingAABB.lx = convertedPoint.x;
                movingAABB.ly = convertedPoint.y;
            }
            else if(event.mouse.btn == robot2D::Mouse::MouseRight) {
                m_animations[m_currentAnimation][collisionPair.second].borderColor = robot2D::Color::Magenta;
            }
        }
        else {
            if(event.mouse.btn != robot2D::Mouse::MouseMiddle) {
                startedPressed = true;
                movingAABB.lx = convertedPoint.x;
                movingAABB.ly = convertedPoint.y;
            }
        }
    }

    void ViewerScene::onMouseReleased(const robot2D::Event& event) {
        if(m_panelManager.isMouseIsOver())
            return;

        if(updateAABBit == -1) {
            auto dd = viewer::DebugCollider{};
            dd.aabb = movingAABB;
            m_animations[m_currentAnimation].addFrame(dd, m_animatedSprite.getPosition());
        } else {
            m_animations[m_currentAnimation][updateAABBit].aabb = movingAABB;
        }

        startedPressed = false;
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            movingAABB = {};
            updateAABBit = -1;
        }
    }

    void ViewerScene::onKeyboardPressed(const robot2D::Event& event) {
        if(event.key.code == robot2D::Key::A) {
            sheetAnimation.reset();
            sheetAnimation.setFlip(false);
        }

        if(event.key.code == robot2D::Key::D) {
            sheetAnimation.reset();
            sheetAnimation.setFlip(true);
        }

        if(event.key.code == robot2D::Key::DEL) {
            if(updateAABBit != -1) {
                m_animations[m_currentAnimation].eraseFrame(updateAABBit);

                updateAABBit = -1;
                movingAABB = {};
            }
        }

        if(event.key.code == robot2D::Key::S) {
            // need save file dialog
            viewer::AnimationIO animationIo{};

            animationIo.saveToFile(
                    "output.xml",
                    m_spriteSheet.getAnimations(),
                    m_animatedSprite.getPosition()
            );
        }
    }


    void ViewerScene::onAddAnimation(const AddAnimationMessage& message) {
        ViewerAnimation viewerAnimation{};
        viewerAnimation.getAnimation().title = message.name;
        m_animations.emplace_back(std::move(viewerAnimation));
        m_currentAnimation = m_animations.size() - 1;

        auto& viewerPanel = m_panelManager.getPanel<ViewerPanel>();
        auto& animationPanel = m_panelManager.getPanel<AnimationPanel>();
        auto* sheet = viewerPanel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerScene::onDeleteAnimation(const DeleteAnimationMessage& message) {
        assert(message.deleteIndex < m_animations.size());
        m_animations.erase(m_animations.begin() + message.deleteIndex);
        m_currentAnimation = message.switchToIndex;

        auto& panel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = panel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerScene::onSwitchAnimation(const SwitchAnimationMessage& message) {
        m_currentAnimation = message.indexTo;
        auto& panel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = panel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

}
