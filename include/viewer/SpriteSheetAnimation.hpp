#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include "SpriteSheet.hpp"

namespace viewer {
    class SpriteSheetAnimation: public robot2D::Drawable {
    public:
        SpriteSheetAnimation();
        ~SpriteSheetAnimation() override = default;

        void setAnimation(Animation* animation);
        void setAnimationRender(robot2D::Sprite& animationRender);
        robot2D::Sprite* getAnimationRender();

        void setFlip(const bool& flag);
        [[nodiscard]] const bool& isFlipped() const;

        [[nodiscard]] const int& getCurrentFrame() const;
        [[nodiscard]] size_t getFramesCount() const;

        int* getSpeed();

        void reset();

        void increaseVisibleFrames();
        void decreaseVisibleFrames();

        [[nodiscard]] const int& getVisibleFrameCounts() const;

        void update(float dt);
        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        Animation* m_animation;
        robot2D::Sprite* m_animatedSprite;

        float m_currentFrame;
        bool m_flip;
        int m_visibleFrameCounts{0};
    };

} // namespace viewer

