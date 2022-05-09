#include <robot2D/Graphics/RenderTarget.hpp>
#include "viewer/SpriteSheetAnimation.hpp"

SpriteSheetAnimation::SpriteSheetAnimation():
m_currentFrame(0.f),
m_flip(false),
m_speed(8.f),
m_animatedSprite{nullptr},
m_spriteSheet{nullptr}
{}


void SpriteSheetAnimation::setSpriteSheet(SpriteSheet& spriteSheet) {
    m_spriteSheet = &spriteSheet;
}

void SpriteSheetAnimation::update(float dt) {
    if(m_animatedSprite == nullptr || m_spriteSheet -> empty())
        return;
    auto& animation = m_spriteSheet -> getAnimations()[0];
    m_currentFrame += m_speed * dt;
    if((int)m_currentFrame >= animation.frames.size())
        m_currentFrame = 0.f;

    if(m_flip)
        m_animatedSprite -> setTextureRect(animation.flip_frames[int(m_currentFrame)]);
    else
        m_animatedSprite->setTextureRect(animation.frames[int(m_currentFrame)]);

    auto frame = animation.frames[int(m_currentFrame)];
    //m_animatedSprite -> setSize({frame.width, frame.height});
}

void SpriteSheetAnimation::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const {
    target.draw(*m_animatedSprite);
}

void SpriteSheetAnimation::setAnimationRender(robot2D::Sprite& animationRender) {
    m_animatedSprite = &animationRender;
    if(m_spriteSheet) {
        auto &animation = m_spriteSheet->getAnimations()[0];
        m_animatedSprite->setTextureRect(animation.frames[int(m_currentFrame)]);
    }
}

robot2D::Sprite* SpriteSheetAnimation::getSprite() {
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

const size_t SpriteSheetAnimation::getFramesCount() const {
    if(m_spriteSheet -> empty())
        return 0;

    if(!m_flip)
        return m_spriteSheet->getAnimations()[0].frames.size();
    else
        return m_spriteSheet->getAnimations()[0].flip_frames.size();
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


