

#include <robot2D/Util/Logger.hpp>
#include <robot2D/Graphics/GL.hpp>
#include <GLFW/glfw3.h>
#include <viewer/ViewerScene.hpp>
#include <viewer/AnimationIO.hpp>

namespace {
    constexpr char* xmlAnimationPath = "res/animations/ZombieBoss/BossWalk.xml";
    constexpr char* pngAnimationPath = "res/animations/ZombieBoss/BossWalk.png";
    //constexpr char* pngAnimationPath = "res/animations/ZombieBoss/1png.png";
}

class TgaWriter {
public:
    TgaWriter();
    ~TgaWriter() = default;

    bool saveToFile(const std::string& path);
private:

};

typedef struct
{
    unsigned char head[12];
    short dx /* Width */, dy /* Height */, head2;
    unsigned char pic[768 * 1024 * 10][3];
} typetga;
typetga tga;

char captureName[256];
unsigned long captureNo;
unsigned char tgahead[12] = {0x00, 0x00, 0x02, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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

struct Quad: public robot2D::Drawable {
    robot2D::Color color;
    robot2D::vec2f position;
    robot2D::vec2f size;
    robot2D::FloatRect aabb;

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



void printColor(int x, int y) {
    unsigned char pixel[4];

    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    std::cout << "R: " << (int)pixel[0] << std::endl;
    std::cout << "G: " << (int)pixel[1] << std::endl;
    std::cout << "B: " << (int)pixel[2] << std::endl;
    std::cout << "A: " << (int)pixel[3] << std::endl;
    std::cout << std::endl;

}


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

bool startedPressed = false;
int updateAABBit = -1;
robot2D::FloatRect movingAABB;
robot2D::Color selectColor = robot2D::Color::Green;
std::vector<DebugCollider> debugAABBs;
std::vector<robot2D::FloatRect> animationAABBs;
Animation animation;

ViewerScene::ViewerScene(robot2D::RenderWindow& window):
    m_window(window) {
}


void ViewerScene::setup() {

   // m_panelManager.addPanel<MenuPanel>(PanelIDS::MenuPanelID);
    m_panelManager.addPanel<ViewerPanel>(PanelIDS::ViewerPanelID);

    m_texture.loadFromFile(pngAnimationPath);

    m_animatedSprite.setTexture(m_texture);
    m_animatedSprite.setPosition({m_texture.getSize().as<float>().x / 2.F, 300.F});
    std::cout << "Tex Size = " <<m_texture.getSize().y << "\n";
    m_Sprite = m_animatedSprite;

    animation.title = "New Animation";
    animation.delay = 150;

//    m_animations.emplace_back(std::move(animation));
//    m_spriteSheet.setAnimations({animation});
    sheetAnimation.setAnimationRender( m_animatedSprite );
    sheetAnimation.setSpriteSheet( m_spriteSheet );

    auto viewer = m_panelManager.getPanel<ViewerPanel>(PanelIDS::ViewerPanelID);
    viewer -> setSpriteSheetAnimation(&sheetAnimation);
}

void ViewerScene::handleEvents(const robot2D::Event& event) {
    m_panelManager.handleEvents(event);

    if(event.type == robot2D::Event::MouseMoved
        && startedPressed) {
        robot2D::vec2f movePos{event.move.x, event.move.y};
        movingAABB.width = movePos.x - movingAABB.lx;
        movingAABB.height = movePos.y - movingAABB.ly;
    }

    if(event.type == robot2D::Event::MousePressed) {
        robot2D::vec2i convertedPoint{event.mouse.x, event.mouse.y};

        if(debugAABBs.empty() && event.mouse.btn == robot2D::MouseLeft) {
            startedPressed = true;
            movingAABB.lx = convertedPoint.x;
            movingAABB.ly = convertedPoint.y;
        }

        int index = 0;
        selectColor = robot2D::Color::Green;
        for(auto& it: debugAABBs) {
            if(it.aabb.contains(convertedPoint.as<float>())) {
                movingAABB = it.aabb;
                updateAABBit = index;
                if(event.mouse.btn == robot2D::MouseLeft) {
                    movingAABB.lx = convertedPoint.x;
                    movingAABB.ly = convertedPoint.y;
                }
                if(event.mouse.btn == robot2D::MouseRight)
                    selectColor = robot2D::Color::Magenta;
                break;
            }
            ++index;
        }

        if(index >= 0 && event.mouse.btn == robot2D::MouseLeft) {
            startedPressed = true;
            movingAABB.lx = convertedPoint.x;
            movingAABB.ly = convertedPoint.y;
        }
    }

    if(event.type == robot2D::Event::MouseReleased) {
        if(updateAABBit == -1) {
            auto dd = DebugCollider{};
            dd.aabb = movingAABB;
            debugAABBs.push_back(dd);

            robot2D::IntRect animationFrame({movingAABB.lx, movingAABB.ly,
                                             movingAABB.width, movingAABB.height});
            robot2D::IntRect animationFrameFlip({movingAABB.lx + movingAABB.width,
                                                 movingAABB.ly,
                                                 -movingAABB.width,
                                                 movingAABB.height});
            auto* anim = m_spriteSheet.getAnimation(0);
            if(anim) {
                anim -> frames.emplace_back(std::move(animationFrame));
                anim -> flip_frames.emplace_back(std::move(animationFrameFlip));
            }
        } else {
            debugAABBs[updateAABBit].aabb = movingAABB;
        }

        startedPressed = false;
        if(event.mouse.btn == robot2D::Mouse::MouseLeft) {
            movingAABB = {};
            updateAABBit = -1;
        }

    }

    if(event.type == robot2D::Event::KeyPressed) {
        if(event.key.code == robot2D::Key::L) {
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
        if(event.key.code == robot2D::Key::DEL) {
            if(updateAABBit != -1) {
                debugAABBs.erase(debugAABBs.begin() + updateAABBit);

                auto* anim = m_spriteSheet.getAnimation(0);
                if(anim) {
                    anim -> frames.erase(anim -> frames.begin() + updateAABBit);
                    anim -> flip_frames.erase(anim -> flip_frames.begin() + updateAABBit);
                }

                updateAABBit = -1;
                movingAABB = {};
            }
        }
        if(event.key.code == robot2D::Key::S) {
            viewer::AnimationIO animationIo{};

            animationIo.saveToFile("output.xml", m_spriteSheet.getAnimations(),
                                   m_animatedSprite.getPosition());
        }
    }

}

void ViewerScene::update(float dt) {
    if(robot2D::Keyboard::isKeyPressed(robot2D::Key::A)) {
        if(sheetAnimation.isFlipped()) {
            sheetAnimation.setFlip(false);
            sheetAnimation.reset();
        }
    }

    if(robot2D::Keyboard::isKeyPressed(robot2D::Key::D)) {
        if(!sheetAnimation.isFlipped()) {
            sheetAnimation.setFlip(true);
            sheetAnimation.reset();
        }
    }

    sheetAnimation.update(dt);
    m_panelManager.update(dt);
}

void ViewerScene::render() {
    m_window.beforeRender();
    m_window.draw(m_Sprite);
    for(auto& it: debugAABBs)
        m_window.draw(it);
    if(startedPressed) {
        DebugCollider debugCollider;
        debugCollider.aabb = movingAABB;
        debugCollider.borderColor = selectColor;
        m_window.draw(debugCollider);
    }
    m_window.afterRender();
    m_panelManager.render();
}
