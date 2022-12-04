#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/Sprite.hpp>

#include "SpriteSheet.hpp"
#include "PanelManager.hpp"
#include "SpriteSheetAnimation.hpp"
#include "Camera2D.hpp"
#include "DebugCollider.hpp"
#include "EventBinder.hpp"

namespace viewer {

    class ViewerScene {
    public:
        ViewerScene();
        ViewerScene(const ViewerScene& other) = delete;
        ViewerScene& operator=(const ViewerScene& other) = delete;
        ViewerScene(ViewerScene&& other) = delete;
        ViewerScene& operator=(ViewerScene&& other) = delete;
        ~ViewerScene() = default;

        void setup(robot2D::RenderWindow* window);

        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void render();
    private:
        void onMousePressed(const robot2D::Event& event);
        void onMouseReleased(const robot2D::Event& event);
        void onKeyboardPressed(const robot2D::Event& event);

        void setupResources();
        void setupBindings();
    private:
        robot2D::RenderWindow* m_window;

        viewer::PanelManager m_panelManager;
        viewer::Camera2D m_camera2D;
        viewer::SpriteSheet m_spriteSheet;
        viewer::SpriteSheetAnimation sheetAnimation;
        EventBinder m_eventBinder;

        robot2D::Texture m_texture;
        robot2D::Sprite m_animatedSprite;
        robot2D::Sprite m_Sprite;


        std::vector<viewer::Animation> m_animations;

        std::vector<viewer::DebugCollider> debugAABBs;
        std::vector<robot2D::FloatRect> animationAABBs;
        viewer::Animation animation;


        robot2D::FloatRect movingAABB;
        robot2D::Color selectColor = robot2D::Color::Green;

        bool startedPressed = false;
        int updateAABBit = -1;
    };


}
