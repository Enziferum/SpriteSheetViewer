#pragma once
#include <vector>

#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Image.hpp>
#include<robot2D/Graphics/FrameBuffer.hpp>

namespace viewer {
    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region,
                                           const robot2D::FrameBuffer::Ptr& frameBuffer,
                                           robot2D::ImageColorFormat imageColorFormat = robot2D::RGBA);

    robot2D::Color readPixel(robot2D::vec2f mousePos);
    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region);

    bool contains(const robot2D::IntRect& l, const robot2D::IntRect& r);
} // namespace viewer