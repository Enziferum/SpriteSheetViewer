#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/Sprite.hpp>

#include "SpriteSheet.hpp"
#include "PanelManager.hpp"
#include "SpriteSheetAnimation.hpp"

class ViewerScene {
public:
    ViewerScene(robot2D::RenderWindow&);
    ~ViewerScene() = default;

    void setup();

    void handleEvents(const robot2D::Event& event);
    void update(float dt);
    void render();
private:
    robot2D::RenderWindow& m_window;
    PanelManager m_panelManager;


    robot2D::Texture m_texture;
    robot2D::Sprite m_animatedSprite;
    robot2D::Sprite m_Sprite;

    SpriteSheet m_spriteSheet;
    SpriteSheetAnimation sheetAnimation;

    std::vector<Animation> m_animations;
};

