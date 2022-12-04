#include <robot2D/Graphics/GL.hpp>
#include <viewer/utils.hpp>

namespace viewer {
    std::vector<robot2D::Color> readPixels(const robot2D::IntRect& region,
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
        glReadPixels(region.lx, region.ly, region.width, region.height, format, GL_UNSIGNED_BYTE, pixels);
        std::vector<robot2D::Color> colors;
        for(int i = 0; i < colorSize * region.width * region.height; i += 4)
            colors.emplace_back(robot2D::Color::fromGL(pixels[0], pixels[1], pixels[2], pixels[3]));
        return colors;
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