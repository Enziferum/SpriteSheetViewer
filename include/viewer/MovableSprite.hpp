#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include "Collider.hpp"

namespace viewer {
    class MovableSprite: public robot2D::Drawable {
    public:
        MovableSprite();
        ~MovableSprite() override = default;

        MovableSprite& operator=(const robot2D::Sprite& sprite);
        void setPosition(const robot2D::vec2f& position);
        void setSprite(const robot2D::Sprite& sprite);

        void isDrawCollider(bool flag);
        robot2D::IntRect getGlobalBounds() const;

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override;
    private:
        robot2D::Sprite m_sprite;
        Collider m_collider;
        bool m_drawCollider{true};
    };
}