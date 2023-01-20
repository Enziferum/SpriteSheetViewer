#pragma once

#include <robot2D/Graphics/Sprite.hpp>

namespace viewer {
    class MovableSprite: public robot2D::Drawable {
    public:
        MovableSprite& operator=(const robot2D::Sprite& sprite) {
            setSprite(sprite);
            return *this;
        }

        void setPosition(const robot2D::vec2f& position) {
            m_sprite.setPosition(position);
        }

        void setSprite(const robot2D::Sprite& sprite) {
            m_sprite = sprite;
            auto bounds = m_sprite.getGlobalBounds();
            auto size = m_sprite.getSize();
            m_collider.setRect({bounds.lx, bounds.ly}, {bounds.width, bounds.height});
        }

        void isDrawCollider(bool flag) { m_drawCollider = flag; }

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
            (void)states;
            if(m_drawCollider)
                target.draw(m_collider);
            target.draw(m_sprite);
        }
    private:
        robot2D::Sprite m_sprite;
        Collider m_collider;
        bool m_drawCollider{false};
    };
}