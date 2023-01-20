#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include "SpriteSheet.hpp"
#include "SpriteSheetAnimation.hpp"
#include "MovableSprite.hpp"
#include "SceneGrid.hpp"

namespace viewer {
    class ViewerView: public robot2D::Drawable {
    public:
        ViewerView();
        ~ViewerView() override = default;

        void setup();
        void update(float dt);
        void processImage();

        SpriteSheetAnimation* getAnimation() const;
    protected:
        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        SpriteSheet m_spriteSheet;
        SpriteSheetAnimation sheetAnimation;
        robot2D::FrameBuffer::Ptr m_frameBuffer;
        robot2D::Texture m_texture;
        robot2D::Sprite m_animatedSprite;
        MovableSprite m_sprite;
        SceneGrid m_sceneGrid;

        robot2D::FloatRect movingAABB;
        robot2D::Color selectColor = robot2D::Color::Green;
    };
}