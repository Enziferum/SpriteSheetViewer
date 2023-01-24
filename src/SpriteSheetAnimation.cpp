#include <robot2D/Graphics/RenderTarget.hpp>
#include <viewer/SpriteSheetAnimation.hpp>

namespace viewer {

    SpriteSheetAnimation::SpriteSheetAnimation():
            m_animation{nullptr},
            m_animatedSprite{nullptr},
            m_currentFrame{0.f},
            m_flip(false)
    {}

    void SpriteSheetAnimation::setAnimation(Animation* animation) {
        m_animation = animation;
    }

    void SpriteSheetAnimation::update(float dt) {
        if(m_animatedSprite == nullptr || m_animation == nullptr || !m_animation -> valid())
            return;

        if(m_visibleFrameCounts == -1)
            m_visibleFrameCounts = m_animation -> frames.size();

        m_currentFrame += m_animation -> delay * dt;
        if((int)m_currentFrame >= m_animation -> frames.size())
            m_currentFrame = 0.f;

        if(m_flip)
            m_animatedSprite -> setTextureRect(m_animation -> flip_frames[int(m_currentFrame)]);
        else
            m_animatedSprite -> setTextureRect(m_animation -> frames[int(m_currentFrame)]);
    }

    void SpriteSheetAnimation::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const {
        target.draw(*m_animatedSprite);
    }

    void SpriteSheetAnimation::setAnimationRender(robot2D::Sprite& animationRender) {
        m_animatedSprite = &animationRender;
        if(m_animation) {
            m_animatedSprite -> setTextureRect(m_animation -> frames[int(m_currentFrame)]);
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

    int* SpriteSheetAnimation::getSpeed() {
        if(m_animation)
            return &m_animation -> delay;
        return nullptr;
    }

    void SpriteSheetAnimation::reset() {
        m_currentFrame = 0.f;
    }

    void SpriteSheetAnimation::increaseVisibleFrames() {
        if(!m_animation || !m_animation -> valid())
            return;
        if(m_visibleFrameCounts < m_animation -> frames.size())
            ++m_visibleFrameCounts;
    }

    void SpriteSheetAnimation::decreaseVisibleFrames() {
        if(m_visibleFrameCounts > 0)
            --m_visibleFrameCounts;
    }

    const int& SpriteSheetAnimation::getVisibleFrameCounts() const {
        return m_visibleFrameCounts;
    }

}
