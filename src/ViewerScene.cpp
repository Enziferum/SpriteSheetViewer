#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerScene.hpp>
#include <viewer/AnimationIO.hpp>

#include <viewer/panels/MenuPanel.hpp>
#include <viewer/panels/ViewerPanel.hpp>

namespace viewer {
    ViewerScene::ViewerScene(): m_window{nullptr} {}

    void ViewerScene::setupResources() {
        auto spritePosition = robot2D::vec2f {
                m_texture.getSize().as<float>().x / 2.F,
                300.F
        };

        m_animatedSprite.setTexture(m_texture);
        m_animatedSprite.setPosition(spritePosition);

        m_Sprite = m_animatedSprite;

        animation.title = "New Animation";
        animation.delay = 150;

        auto viewer = m_panelManager.getPanel<viewer::ViewerPanel>();
        viewer.setSpriteSheetAnimation(&sheetAnimation);
    }

    void ViewerScene::setupBindings() {
        m_eventBinder.bindEvent(robot2D::Event::MouseMoved, [this](const robot2D::Event& event) {
            if(startedPressed) {
                robot2D::vec2f movePos{event.move.x, event.move.y};
                RB_INFO("Mouse moved at point {0}:{1}", movePos.x, movePos.y);
                movingAABB.width = movePos.x - movingAABB.lx;
                movingAABB.height = movePos.y - movingAABB.ly;
            }
        });

        m_eventBinder.bindEvent(robot2D::Event::MousePressed, BIND_CLASS_FN(onMousePressed));
        m_eventBinder.bindEvent(robot2D::Event::MouseReleased, BIND_CLASS_FN(onMouseReleased));
        m_eventBinder.bindEvent(robot2D::Event::KeyPressed, BIND_CLASS_FN(onKeyboardPressed));
    }

    void ViewerScene::setup(robot2D::RenderWindow* window) {
        m_window = window;
        m_panelManager.addPanel<viewer::MenuPanel>();
        m_panelManager.addPanel<viewer::ViewerPanel>();
        auto winSize = m_window -> getSize();
        m_camera2D.resetViewport(winSize.as<float>());

        setupResources();
        setupBindings();
    }


    void ViewerScene::onMousePressed(const robot2D::Event& event) {
        robot2D::vec2i convertedPoint{event.mouse.x, event.mouse.y};
        RB_INFO("Mouse pressed at point {0}:{1}", convertedPoint.x, convertedPoint.y);

        if(debugAABBs.empty() && event.mouse.btn == robot2D::MouseLeft) {
            startedPressed = true;
            movingAABB.lx = convertedPoint.x;
            movingAABB.ly = convertedPoint.y;
        }

        int index = 0;
        selectColor = robot2D::Color::Green;
        for(auto& debug: debugAABBs) {
            if(debug.aabb.contains(convertedPoint.as<float>())) {
                movingAABB = debug.aabb;
                updateAABBit = index;
                if(event.mouse.btn == robot2D::MouseLeft) {
                    movingAABB.lx = convertedPoint.x;
                    movingAABB.ly = convertedPoint.y;
                }
                if(event.mouse.btn == robot2D::MouseRight)
                    selectColor = robot2D::Color::Magenta;
                break;
            }
            ++index;
        }

        if(index >= 0 && event.mouse.btn == robot2D::MouseLeft) {
            startedPressed = true;
            movingAABB.lx = convertedPoint.x;
            movingAABB.ly = convertedPoint.y;
        }
    }

    void ViewerScene::onMouseReleased(const robot2D::Event& event) {
        if(updateAABBit == -1) {
            auto dd = viewer::DebugCollider{};
            dd.aabb = movingAABB;
            debugAABBs.push_back(dd);

            robot2D::IntRect animationFrame({movingAABB.lx, movingAABB.ly,
                                             movingAABB.width, movingAABB.height});
            robot2D::IntRect animationFrameFlip({movingAABB.lx + movingAABB.width,
                                                 movingAABB.ly,
                                                 -movingAABB.width,
                                                 movingAABB.height});
            auto* anim = m_spriteSheet[0];
            if(anim) {
                anim -> frames.emplace_back(std::move(animationFrame));
                anim -> flip_frames.emplace_back(std::move(animationFrameFlip));
            }
        } else {
            debugAABBs[updateAABBit].aabb = movingAABB;
        }

        startedPressed = false;
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            movingAABB = {};
            updateAABBit = -1;
        }
    }

    void ViewerScene::onKeyboardPressed(const robot2D::Event& event) {
        if(event.key.code == robot2D::Key::L) {
            viewer::Animation anim{"Default", 150};

            for(auto& debug: debugAABBs)
                anim.addFrame(debug.aabb);

            m_spriteSheet.setAnimations({anim});
            sheetAnimation.setAnimationRender( m_animatedSprite);
        }
        if(event.key.code == robot2D::Key::DEL) {
            if(updateAABBit != -1) {
                debugAABBs.erase(debugAABBs.begin() + updateAABBit);

                auto* anim = m_spriteSheet[0];
                if(anim) {
                    anim -> frames.erase(anim -> frames.begin() + updateAABBit);
                    anim -> flip_frames.erase(anim -> flip_frames.begin() + updateAABBit);
                }

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


    void ViewerScene::handleEvents(const robot2D::Event& event) {
        m_panelManager.handleEvents(event);
        m_eventBinder.handleEvents(event);
    }

    void ViewerScene::update(float dt) {
        sheetAnimation.update(dt);
        m_panelManager.update(dt);
        m_camera2D.update(dt);
    }

    void ViewerScene::render() {
        m_window -> beforeRender();
        m_window -> setView(m_camera2D.getView());

        for(auto& debug: debugAABBs)
            m_window -> draw(debug);

        if(startedPressed) {
            viewer::DebugCollider debugCollider;
            debugCollider.aabb = movingAABB;
            debugCollider.borderColor = selectColor;
            m_window -> draw(debugCollider);
        }

        m_window -> afterRender();
        m_panelManager.render();
    }

}
