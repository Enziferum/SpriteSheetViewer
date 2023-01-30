#include <cassert>
#include <robot2D/Graphics/GL.hpp>
#include <viewer/Utils.hpp>

namespace viewer::util {
    robot2D::Color readPixel(robot2D::vec2f mousePos) {
        unsigned char pixels[4];
        glReadPixels(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y),
                     1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        return {
            static_cast<float>(pixels[0]), static_cast<float>(pixels[1]),
            static_cast<float>(pixels[2]), static_cast<float>(pixels[3])
        };
    }

    void applyImageMask(robot2D::Image& image, robot2D::Color imageMask) {
        auto colorFormat = image.getColorFormat();
        assert(colorFormat == robot2D::ImageColorFormat::RGBA && "Avalable apply image mask only to RGBA color format");
        auto* buffer = image.getBuffer();
        assert(buffer != nullptr && "Load image before apply mask");
        const auto& size = image.getSize();

        for(int i = 0; i < static_cast<int>(size.x * size.y * 4); i += 4) {
            if(buffer[i] == imageMask.red && buffer[i + 1] == imageMask.green && buffer[i + 2] == imageMask.blue) {
                buffer[i + 3] = 0;
            }
        }
    }
} // namespace viewer::util