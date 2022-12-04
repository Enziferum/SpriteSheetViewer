#pragma once

#include <array>
#include <robot2D/Graphics/Drawable.hpp>

namespace viewer {
    struct DebugCollider: public robot2D::Drawable {
        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
            std::array<robot2D::Transform, 4> quads;
            quads[0].translate(aabb.lx, aabb.ly);
            quads[0].scale(aabb.width,borderSize);

            quads[1].translate(aabb.lx, aabb.ly);
            quads[1].scale(borderSize, aabb.height);

            quads[2].translate(aabb.lx, aabb.ly + aabb.height);
            quads[2].scale(aabb.width,borderSize);

            quads[3].translate(aabb.lx + aabb.width, aabb.ly);
            quads[3].scale(borderSize,aabb.height);

            for(auto& it: quads) {
                states.transform = it;
                states.color = borderColor;
                states.texture = texture;
                target.draw(states);
            }
        }

        float borderSize = 1.F;
        robot2D::FloatRect aabb;
        robot2D::Color borderColor = robot2D::Color::Green;
        robot2D::Texture* texture{nullptr};
    };

}