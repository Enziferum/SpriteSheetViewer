#pragma once

#include <robot2D/Graphics/RenderTarget.hpp>
#include <robot2D/Graphics/Texture.hpp>

namespace viewer {
    struct Quad: public robot2D::Drawable {

        [[nodiscard]]
        robot2D::FloatRect getFrame() const;
        void draw(robot2D::RenderTarget& target,
                  robot2D::RenderStates states) const override;

        robot2D::vec2f position;
        robot2D::vec2f size;
        robot2D::Color color;
        robot2D::Texture* texture{nullptr};
    };
}