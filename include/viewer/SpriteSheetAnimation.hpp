#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include "SpriteSheet.hpp"

namespace viewer {
    class SpriteSheetAnimation: public robot2D::Drawable {
    public:
        SpriteSheetAnimation();
        ~SpriteSheetAnimation() = default;

        void setAnimation(Animation& animation);
        void setAnimationRender(robot2D::Sprite& animationRender);
        robot2D::Sprite* getAnimationRender();

        void setFlip(const bool& flag);
        const bool& isFlipped() const;

        const int& getCurrentFrame() const;
        const size_t getFramesCount() const;

        void setSpeed(const float& speed);
        const float& getSpeed() const;
        float& getSpeed();

        void reset();

        void increaseVisibleFrames() {
            if(!m_animation || !m_animation -> valid())
                return;
            if(m_visibleFrameCounts < m_animation -> frames.size())
                ++m_visibleFrameCounts;
        }
        void decreaseVisibleFrames() {
            if(m_visibleFrameCounts > 0)
                --m_visibleFrameCounts;
        }

        const int& getVisibleFrameCounts() const {
            return m_visibleFrameCounts;
        }

        void update(float dt);
        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        Animation* m_animation;
        robot2D::Sprite* m_animatedSprite;

        bool m_flip;
        float m_currentFrame;
        float m_speed;
        int m_visibleFrameCounts{-1};
    };

}

