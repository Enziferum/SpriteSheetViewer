#pragma once

#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/Rect.hpp>

namespace viewer {
    robot2D::Color readPixel(robot2D::vec2f mousePos);

    bool contains(const robot2D::IntRect& l, const robot2D::IntRect& r);
} // namespace viewer