#include "viewer/ViewerScene.hpp"
#include <robot2D/Util/Logger.hpp>
#include <robot2D/Graphics/GL.hpp>
#include <GLFW/glfw3.h>

namespace {
    constexpr char* xmlAnimationPath = "res/animations/ZombieBoss/BossWalk.xml";
    constexpr char* pngAnimationPath = "res/animations/ZombieBoss/BossWalk.png";
    //constexpr char* pngAnimationPath = "res/animations/ZombieBoss/1png.png";
}

ViewerScene::ViewerScene(robot2D::RenderWindow& window):
    m_window(window) {
}


struct Quad: public robot2D::Drawable {
    robot2D::Color color;
    robot2D::vec2f position;
    robot2D::vec2f size;
    robot2D::FloatRect aabb;
    bool updatedAABB = false;

    robot2D::FloatRect& getAABB() {
    if(aabb == robot2D::FloatRect{})
        aabb = {position.x, position.y, size.x, size.y};
    return aabb;
    }

    void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
    robot2D::Transform transform;
    transform.translate(position);
    transform.scale(size);

    states.transform *= transform;
    states.color = color;
    target.draw(states);
    }
};

struct DebugCollider: public robot2D::Drawable{
    float borderSize = 1.F;
    robot2D::FloatRect aabb;
    robot2D::Color borderColor = robot2D::Color::Green;
    robot2D::Texture* texture;

    void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
        std::array<robot2D::Transform, 4> quads;
        quads[0].translate(aabb.lx, aabb.ly);
        quads[0].scale(aabb.width,borderSize);

        quads[1].translate(aabb.lx, aabb.ly);
        quads[1].scale(borderSize, aabb.height);

        quads[2].translate(aabb.lx, aabb.ly + aabb.height);
        quads[2].scale(aabb.width,borderSize);

        quads[3].translate(aabb.lx + aabb.width, aabb.ly);
        quads[3].scale(borderSize,aabb.height);

        for(auto& it: quads) {
            states.transform = it;
            states.color = borderColor;
            states.texture = texture;
            target.draw(states);
        }
    }
};

std::vector<DebugCollider> debugAABBs;

void ViewerScene::setup() {

    m_panelManager.addPanel<MenuPanel>(PanelIDS::MenuPanelID);
    m_panelManager.addPanel<ViewerPanel>(PanelIDS::ViewerPanelID);


    //m_spriteSheet.loadFromFile(xmlAnimationPath);
    m_texture.loadFromFile(pngAnimationPath);


    const auto* pixelBuffer = m_texture.getPixels();
    auto textureSize = m_texture.getSize();
    int channelsValue = m_texture.getColorFormat();

    struct PixelInfo {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        bool valid() {
            return (a != 0);
        }
    };

        std::cout<< "Pixel components: red = " << int(pixelBuffer[0]) << " green = "
             << int(pixelBuffer[1]) << " blue = "
             << int(pixelBuffer[2]) << " alpha = "
             << int(pixelBuffer[3]) <<  std::endl;

    m_animatedSprite.setTexture(m_texture);
    m_animatedSprite.setPosition({m_texture.getSize().as<float>().x / 2.F, 300.F});

//    sheetAnimation.setSpriteSheet( m_spriteSheet );
//    sheetAnimation.setAnimationRender( m_animatedSprite);
//
    auto viewer = m_panelManager.getPanel<ViewerPanel>(PanelIDS::ViewerPanelID);
    viewer -> setSpriteSheetAnimation(&sheetAnimation);
}

void printColor(int x, int y) {
    unsigned char pixel[4];

    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    std::cout << "R: " << (int)pixel[0] << std::endl;
    std::cout << "G: " << (int)pixel[1] << std::endl;
    std::cout << "B: " << (int)pixel[2] << std::endl;
    std::cout << "A: " << (int)pixel[3] << std::endl;
    std::cout << std::endl;

}

typedef struct
{
    unsigned char head[12];
    short dx /* Width */, dy /* Height */, head2;
    unsigned char pic[768 * 1024 * 10][3];
} typetga;
typetga tga;

char captureName[256];
unsigned long captureNo;
unsigned char tgahead[12] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void capture(GLFWwindow* window)
{
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); /* Get size, store into specified variables  */

    /* Prepare the targa header */
    memcpy(tga.head, tgahead, 12);
    tga.dx = screenWidth;
    tga.dy = screenHeight;
    tga.head2 = 0x2018;

    /* Store pixels into tga.pic */
    glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, tga.pic[0]);

    /* Store "Capture_%04lu.tga" + captureNo into captureName, increase frame count */
    sprintf(captureName, "Capture_%04lu.tga" /* 'lu' for unsigned long */, captureNo); captureNo++;

    /* Write file */
    FILE* cc = fopen(captureName, "wb");
    fwrite(&tga, 1, (18 + 3 * screenWidth * screenHeight), cc);
    fclose(cc);
}

int pressed_Cntr = 0;
robot2D::vec2f leftTop;
robot2D::vec2f rightBottom;

void findBoundingAABB(robot2D::Texture& texture, robot2D::FloatRect fatAABB, robot2D::FloatRect& boundAABB) {
    struct RGBAColor{ unsigned char r, g, b, a;};
    RGBAColor* pixelBuffer = new RGBAColor[int(fatAABB.width) * int(fatAABB.height)];

    float windowHeight = 1280;
    glReadPixels(fatAABB.lx, windowHeight - fatAABB.ly, fatAABB.width, fatAABB.height,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);

    int offsetY = 0;
    int offsetX = 0;
    int maxOffsetX = 0;
    int maxOffsetY = 0;

    for(int it = 0; it < fatAABB.height; ++it) {
        for(int ij = 0; ij < fatAABB.width; ++ij)
            if(pixelBuffer[it + ij].a != 0 ) {
                offsetY = it;
                break;
            }
    }

    for(int it = 0; it < fatAABB.width; ++it) {
        for(int ij = 0; ij < fatAABB.height; ++ij)
            if(pixelBuffer[it + ij].a != 0 ) {
                offsetX = it;
                break;
            }
    }

    boundAABB.lx = fatAABB.lx;
    boundAABB.ly = fatAABB.ly;
    boundAABB.width = fatAABB.width;
    boundAABB.height = fatAABB.height;

    delete[] pixelBuffer;
}

std::vector<robot2D::FloatRect> animationAABBs;

void ViewerScene::handleEvents(const robot2D::Event& event) {
    m_panelManager.handleEvents(event);
    if(event.type == robot2D::Event::MouseMoved) {
       // printColor(event.move.x, event.move.y);
    }

    if(event.type == robot2D::Event::MousePressed) {
        robot2D::vec2i convertedPoint{event.mouse.x, event.mouse.y};
//        auto winSize = m_window.getSize();
//        convertedPoint.y = winSize.y - convertedPoint.y;
//        printColor(convertedPoint.x, convertedPoint.y);
//
        ++pressed_Cntr;
        if(pressed_Cntr == 1)
            leftTop = convertedPoint.as<float>();
        if(pressed_Cntr == 2) {
            rightBottom = convertedPoint.as<float>();

            robot2D::FloatRect fatAABB;
            fatAABB.lx = leftTop.x;
            fatAABB.ly = leftTop.y;
            fatAABB.width = rightBottom.x - leftTop.x;
            fatAABB.height = rightBottom.y - leftTop.y;

            robot2D::FloatRect boundAABB;

            findBoundingAABB(m_texture, fatAABB, boundAABB);
            auto dd = DebugCollider{};
            dd.aabb = boundAABB;
            debugAABBs.push_back(dd);

            pressed_Cntr = 0;
        }

    }

    if(event.type == robot2D::Event::KeyPressed
        && event.key.code == robot2D::Key::L) {
        std::vector<Animation> anims;

        Animation anim;
        anim.title = "Cutted";
        anim.delay = 150;

        for(auto& it: debugAABBs) {
            anim.frames.push_back({it.aabb.lx, it.aabb.ly, it.aabb.width, it.aabb.height});
            anim.flip_frames.push_back({it.aabb.lx + it.aabb.width, it.aabb.ly, -it.aabb.width,
                                        it.aabb.height});
        }

        m_spriteSheet.setAnimations({anim});

        sheetAnimation.setSpriteSheet( m_spriteSheet );
        sheetAnimation.setAnimationRender( m_animatedSprite);
    }

}

void ViewerScene::update(float dt) {
    if(robot2D::Keyboard::isKeyPressed(robot2D::Key::A)) {
        m_animatedSprite.move({ -dt * 100, 0});
        if(sheetAnimation.isFlipped()) {
            sheetAnimation.setFlip(false);
            sheetAnimation.reset();
        }
    }

    if(robot2D::Keyboard::isKeyPressed(robot2D::Key::D)) {
        m_animatedSprite.move({ dt * 100, 0});
        if(!sheetAnimation.isFlipped()) {
            sheetAnimation.setFlip(true);
            sheetAnimation.reset();
        }
    }

    if(robot2D::Keyboard::isKeyPressed(robot2D::Key::U))
        showUI = !showUI;

    sheetAnimation.update(dt);
    m_panelManager.update(dt);
}

void ViewerScene::render() {
    m_window.beforeRender();
    m_window.draw(m_animatedSprite);
    for(auto& it: debugAABBs)
        m_window.draw(it);
    m_window.afterRender();
    m_panelManager.render();
}
