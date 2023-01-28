#include <viewer/MovableSprite.hpp>

namespace viewer {

    MovableSprite::MovableSprite() {
        m_collider.borderColor = robot2D::Color::Black;
    }

    MovableSprite& MovableSprite::operator=(const robot2D::Sprite& sprite) {
        setSprite(sprite);
        return *this;
    }

    void MovableSprite::setPosition(const robot2D::vec2f& position) {
        m_sprite.setPosition(position);
    }

    void MovableSprite::setSprite(const robot2D::Sprite& sprite) {
        m_sprite = sprite;
        auto bounds = m_sprite.getGlobalBounds();
        auto size = m_sprite.getSize();
        m_collider.setRect({bounds.lx, bounds.ly}, {bounds.width, bounds.height});
    }

    void MovableSprite::isDrawCollider(bool flag) { m_drawCollider = flag; }

    void MovableSprite::draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const {
        (void)states;
        if(m_drawCollider)
            target.draw(m_collider);
        target.draw(m_sprite);
    }

    robot2D::IntRect MovableSprite::getGlobalBounds() const {
        auto bounds = m_sprite.getGlobalBounds();
        return {bounds.lx, bounds.ly, bounds.width, bounds.height};
    }

} // namespace viewer