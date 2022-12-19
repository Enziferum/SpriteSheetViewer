#pragma once

#include <array>
#include <robot2D/Graphics/Drawable.hpp>
#include <robot2D/Graphics/RenderTarget.hpp>

#include "Quad.hpp"

namespace viewer {
    struct DebugCollider: public robot2D::Drawable {

        bool notZero() const {
            return aabb.width > 0 && aabb.height > 0;
        }

        bool intersects(const robot2D::FloatRect& rect) {
            return aabb.intersects(rect);
        }

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
            std::array<robot2D::Transform, 4> quads;
            quads[0].translate(aabb.lx, aabb.ly);
            quads[0].scale(aabb.width, borderSize);

            quads[1].translate(aabb.lx, aabb.ly);
            quads[1].scale(borderSize, aabb.height);

            quads[2].translate(aabb.lx, aabb.ly + aabb.height);
            quads[2].scale(aabb.width,borderSize);

            quads[3].translate(aabb.lx + aabb.width, aabb.ly);
            quads[3].scale(borderSize, aabb.height);

            for(const auto& transform: quads) {
                states.transform = transform;
                states.color = borderColor;
                target.draw(states);
            }

            if(showMovePoints) {
                std::array<Quad, 2> moveQ;

                constexpr robot2D::vec2f qSize = {6, 6};

                moveQ[0].position = {aabb.lx - qSize.x / 2.F, aabb.ly - qSize.y / 2.F};
                moveQ[0].size = qSize;
                moveQ[0].color = robot2D::Color::Cyan;

                moveQ[1].position = {
                        aabb.lx + aabb.width - qSize.x / 2.F,
                        aabb.ly + aabb.height - qSize.y / 2.F
                };
                moveQ[1].size = qSize;
                moveQ[1].color = robot2D::Color::Cyan;

                for(const auto& q: moveQ)
                    target.draw(q);
            }
        }

        float borderSize = 1.F;
        robot2D::FloatRect aabb;
        robot2D::Color borderColor = robot2D::Color::Green;
        bool showMovePoints = {false};
    };

}