#pragma once

#include <robot2D/Graphics/RenderTarget.hpp>
#include <robot2D/Graphics/Texture.hpp>

namespace viewer {
    struct Quad: public robot2D::Drawable {
        robot2D::FloatRect& getAABB() {
            if(aabb == robot2D::FloatRect{})
                aabb = {position.x, position.y, size.x, size.y};
            return aabb;
        }

        void draw(robot2D::RenderTarget& target,
                  robot2D::RenderStates states) const override {
            robot2D::Transform transform;
            transform.translate(position);
            transform.scale(size);

            states.transform *= transform;
            states.color = color;
            states.texture = texture;
            target.draw(states);
        }

        robot2D::Color color;
        robot2D::vec2f position;
        robot2D::vec2f size;
        robot2D::Texture* texture{nullptr};
        robot2D::FloatRect aabb;
    };
}