#pragma once
#include <vector>

#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Image.hpp>

namespace viewer {
    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region,
                                           robot2D::ImageColorFormat imageColorFormat = robot2D::RGBA);
}