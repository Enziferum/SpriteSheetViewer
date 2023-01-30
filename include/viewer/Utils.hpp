#pragma once

#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Image.hpp>

namespace viewer::util {
    robot2D::Color readPixel(robot2D::vec2f mousePos);

    void applyImageMask(robot2D::Image& image, robot2D::Color imageMask);
} // namespace viewer::util