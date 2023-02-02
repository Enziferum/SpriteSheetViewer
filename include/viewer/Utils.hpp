#pragma once

#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Image.hpp>

namespace viewer::util {

    struct HashFunction {
        size_t operator()(const robot2D::IntRect& rect) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + std::hash<int>()( rect.lx );
            res = res * 31 + std::hash<int>()( rect.ly );
            res = res * 31 + std::hash<int>()( rect.width );
            res = res * 31 + std::hash<int>()( rect.height );
            return res;
        }
    };


    robot2D::Color readPixel(robot2D::vec2f mousePos);

    void applyImageMask(robot2D::Image& image, robot2D::Color imageMask);
} // namespace viewer::util