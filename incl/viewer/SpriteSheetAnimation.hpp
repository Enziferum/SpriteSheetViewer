#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include "SpriteSheet.hpp"

class SpriteSheetAnimation: public robot2D::Drawable {
public:
    SpriteSheetAnimation();
    ~SpriteSheetAnimation() = default;

    void setSpriteSheet(const SpriteSheet& spriteSheet);
    void setAnimationRender(robot2D::Sprite& animationRender);
    robot2D::Sprite* getSprite();

    void update(float dt);
    void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;

    void setFlip(const bool& flag);
    const bool& isFlipped() const;

    const int& getCurrentFrame() const;
    const size_t getFramesCount() const;

    void setSpeed(const float& speed);
    const float& getSpeed() const;
    float& getSpeed();

    void reset();
private:
    const SpriteSheet* m_spriteSheet;
    robot2D::Sprite* m_animatedSprite;

    bool m_flip;
    float m_currentFrame;
    float m_speed;
};
