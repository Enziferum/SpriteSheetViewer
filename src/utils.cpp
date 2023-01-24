#include <robot2D/Graphics/GL.hpp>
#include <viewer/utils.hpp>

#include <iostream>

namespace viewer {
    robot2D::Color readPixel(robot2D::vec2f mousePos) {
        unsigned char pixels[4];
        glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        return {(int) pixels[0], (int) pixels[1], (int) pixels[2], (int) pixels[3]};
    }

    bool contains(const robot2D::IntRect& l, const robot2D::IntRect& r) {
        if (l.lx <= r.lx && l.ly <= r.ly
            && (l.lx + l.width) >= (r.lx + r.width)
            && (l.ly + l.height) >= (r.ly + r.height))
            return true;
        else
            return false;
    }
}