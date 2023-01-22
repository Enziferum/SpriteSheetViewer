#include <robot2D/Graphics/GL.hpp>
#include <viewer/utils.hpp>

#include <iostream>

namespace viewer {
    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region,
                                           const robot2D::FrameBuffer::Ptr& frameBuffer,
                                           robot2D::ImageColorFormat imageColorFormat) {
        GLenum format;
        int colorSize{0};

        if(imageColorFormat == robot2D::RGB) {
            format = GL_RGB;
            colorSize = 3;
        }

        if(imageColorFormat == robot2D::RGBA) {
            format = GL_RGBA;
            colorSize = 4;
        }

        /// 4 * width * height
        unsigned char* pixels = new unsigned char [colorSize * region.width * region.height];
        glReadPixels(region.lx, region.ly, region.width, region.height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        std::vector<robot2D::Color> colors;
        for(int i = 0; i < colorSize * region.width * region.height; i += 4)
            colors.emplace_back(robot2D::Color{(int)pixels[i], (int)pixels[i + 1], (int)pixels[i + 2], (int)pixels[i + 3]});

        delete[] pixels;

        int cnt = 0;
        for(const auto& color: colors) {
            if(color.red == 255 && color.green == 255 && color.blue == 255 && color.alpha == 255)
                continue;
            else
                ++cnt;
        }

        std::cout << "Not White Pixels = " << cnt << std::endl;

        return colors;
    }

    robot2D::Color readPixel(robot2D::vec2f mousePos) {
        unsigned char pixels[4];
        glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        std::vector<robot2D::Color> colors;
        std::cout << "R: " << (int)pixels[0] << std::endl;
        std::cout << "G: " << (int)pixels[0+1] << std::endl;
        std::cout << "B: " << (int)pixels[0+2] << std::endl;
        std::cout << "A: " << (int)pixels[0+3] << std::endl;
        std::cout << "------------------------" << std::endl;
        return {(int)pixels[0], (int)pixels[1], (int)pixels[2], (int)pixels[3]};
    }

    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region) {
        auto colorSize = 4;
        unsigned char* pixels = new unsigned char [colorSize * region.width * region.height];
        glReadPixels(region.lx, region.ly, region.width, region.height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        std::vector<robot2D::Color> colors;
        for(int i = 0; i < colorSize * region.width * region.height; i += 4) {
            std::cout << "R: " << (int)pixels[i] << std::endl;
            std::cout << "G: " << (int)pixels[i+1] << std::endl;
            std::cout << "B: " << (int)pixels[i+2] << std::endl;
            std::cout << "A: " << (int)pixels[i+3] << std::endl;
            std::cout << "------------------------" << std::endl;
            colors.emplace_back(robot2D::Color{(int)pixels[i], (int)pixels[i + 1], (int)pixels[i + 2], (int)pixels[i + 3]});
        }

        int cnt = 0;
        for(const auto& color: colors) {
            if(color.red == 0 && color.green == 255 && color.blue == 0 )
                ++cnt;
        }

        std::cout << "cnt " << cnt << std::endl;

        return colors;
    }

    bool contains(const robot2D::IntRect& l, const robot2D::IntRect& r) {
        if(l.lx <= r.lx && l.ly <= r.ly
           && (l.lx + l.width) >= (r.lx + r.width)
           && (l.ly + l.height) >= (r.ly + r.height))
            return true;
        else
            return false;
    }

    //struct Tga
//{
//    unsigned char head[12];
//    short dx /* Width */, dy /* Height */, head2;
//    unsigned char pic[768 * 1024 * 10][3];
//} ;
//
//char captureName[256];
//unsigned long captureNo;
//unsigned char tgahead[12] = {0x00, 0x00, 0x02, 0x00, 0x00,
//                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//
//void capture(GLFWwindow* window)
//{
//    int screenWidth, screenHeight;
//    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); /* Get size, store into specified variables  */
//
//    /* Prepare the targa header */
//    memcpy(tga.head, tgahead, 12);
//    tga.dx = screenWidth;
//    tga.dy = screenHeight;
//    tga.head2 = 0x2018;
//
//    /* Store pixels into tga.pic */
//    glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, tga.pic[0]);
//
//    /* Store "Capture_%04lu.tga" + captureNo into captureName, increase frame count */
//    sprintf(captureName, "Capture_%04lu.tga" /* 'lu' for unsigned long */, captureNo); captureNo++;
//
//    /* Write file */
//    FILE* cc = fopen(captureName, "wb");
//    fwrite(&tga, 1, (18 + 3 * screenWidth * screenHeight), cc);
//    fclose(cc);
//}
}