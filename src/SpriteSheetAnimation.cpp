#include <robot2D/Graphics/RenderTarget.hpp>
#include <viewer/SpriteSheetAnimation.hpp>

namespace viewer {

    SpriteSheetAnimation::SpriteSheetAnimation():
            m_animation{nullptr},
            m_animatedSprite{nullptr},
            m_currentFrame{0.f},
            m_speed(8.f),
            m_flip(false)
    {}


    void SpriteSheetAnimation::setAnimation(Animation& animation) {
        m_animation = &animation;
    }

    void SpriteSheetAnimation::update(float dt) {
        if(m_animatedSprite == nullptr || m_animation == nullptr || !m_animation -> valid())
            return;

        if(m_visibleFrameCounts == -1)
            m_visibleFrameCounts = m_animation -> frames.size();

        m_currentFrame += m_speed * dt;
        if((int)m_currentFrame >= m_animation -> frames.size())
            m_currentFrame = 0.f;

        if(m_flip)
            m_animatedSprite -> setTextureRect(m_animation -> flip_frames[int(m_currentFrame)]);
        else
            m_animatedSprite -> setTextureRect(m_animation -> frames[int(m_currentFrame)]);

        auto frame = m_animation -> frames[int(m_currentFrame)];
    }

    void SpriteSheetAnimation::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const {
        target.draw(*m_animatedSprite);
    }

    void SpriteSheetAnimation::setAnimationRender(robot2D::Sprite& animationRender) {
        m_animatedSprite = &animationRender;
        if(m_animation) {
            m_animatedSprite->setTextureRect(m_animation -> frames[int(m_currentFrame)]);
        }
    }

    robot2D::Sprite* SpriteSheetAnimation::getAnimationRender() {
        return m_animatedSprite;
    }

    void SpriteSheetAnimation::setFlip(const bool& flag) {
        m_flip = flag;
    }

    const bool& SpriteSheetAnimation::isFlipped() const {
        return m_flip;
    }

    const int& SpriteSheetAnimation::getCurrentFrame() const {
        return m_currentFrame;
    }

    size_t SpriteSheetAnimation::getFramesCount() const {
        if(!m_animation)
            return 0;

        if(!m_flip)
            return m_animation -> frames.size();
        else
            return m_animation -> flip_frames.size();
    }

    void SpriteSheetAnimation::setSpeed(const float &speed) {
        m_speed = speed;
    }

    const float& SpriteSheetAnimation::getSpeed() const {
        return m_speed;
    }

    float& SpriteSheetAnimation::getSpeed() {
        return m_speed;
    }

    void SpriteSheetAnimation::reset() {
        m_currentFrame = 0.f;
    }



}
