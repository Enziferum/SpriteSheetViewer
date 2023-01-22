#pragma once

#include <array>
#include <robot2D/Graphics/Drawable.hpp>
#include <robot2D/Graphics/RenderTarget.hpp>

#include "Quad.hpp"

namespace viewer {
    struct Collider: public robot2D::Drawable {

        void setPosition(const robot2D::vec2f& position) {
            m_aabb.lx = position.x;
            m_aabb.ly = position.y;
        }

        robot2D::vec2f getPosition() const {
            return {m_aabb.lx, m_aabb.ly};
        }

        void setSize(const robot2D::vec2f& size) {
            m_aabb.width = size.x;
            m_aabb.height = size.y;
        }

        void setRect(const robot2D::vec2f& topLeft, const robot2D::vec2f& size) {
            m_aabb.lx = topLeft.x;
            m_aabb.ly = topLeft.y;
            m_aabb.width = size.x;
            m_aabb.height = size.y;
        }

        void setRect(const robot2D::FloatRect& rect) {
            m_aabb = rect;
        }

        bool contains(const robot2D::vec2f& point)  {
            return m_aabb.contains(point);
        }

        bool notZero() const {
            return m_aabb.width > 0 && m_aabb.height > 0;
        }

        bool intersects(const robot2D::FloatRect& rect) {
            return m_aabb.intersects(rect);
        }

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
            std::array<robot2D::Transform, 4> quads;
            quads[0].translate(m_aabb.lx, m_aabb.ly);
            quads[0].scale(m_aabb.width, borderSize);

            quads[1].translate(m_aabb.lx, m_aabb.ly);
            quads[1].scale(borderSize, m_aabb.height);

            quads[2].translate(m_aabb.lx, m_aabb.ly + m_aabb.height);
            quads[2].scale(m_aabb.width,borderSize);

            quads[3].translate(m_aabb.lx + m_aabb.width, m_aabb.ly);
            quads[3].scale(borderSize, m_aabb.height);

            for(const auto& transform: quads) {
                states.transform = transform;
                states.color = borderColor;
                target.draw(states);
            }

            if(showMovePoints) {
                std::array<Quad, 2> moveQ;

                constexpr robot2D::vec2f qSize = {6, 6};

                moveQ[0].position = {m_aabb.lx - qSize.x / 2.F, m_aabb.ly - qSize.y / 2.F};
                moveQ[0].size = qSize;
                moveQ[0].color = robot2D::Color::Cyan;

                moveQ[1].position = {
                        m_aabb.lx + m_aabb.width - qSize.x / 2.F,
                        m_aabb.ly + m_aabb.height - qSize.y / 2.F
                };
                moveQ[1].size = qSize;
                moveQ[1].color = robot2D::Color::Cyan;

                for(const auto& q: moveQ)
                    target.draw(q);
            }
        }

        const robot2D::FloatRect& getRect() const {
            return m_aabb;
        }

        float borderSize = 1.F;
        robot2D::Color borderColor = robot2D::Color::Green;
        bool showMovePoints = {false};
    private:
        robot2D::FloatRect m_aabb{};
    };

}