#include <filesystem>

#include <robot2D/Graphics/RenderTarget.hpp>
#include <robot2D/Util/Logger.hpp>

#include <viewer/ViewerView.hpp>
#include <viewer/utils.hpp>

namespace viewer {
    namespace {
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
    }

    namespace fs = std::filesystem;

    void ViewerView::setup(const robot2D::vec2i& windowSize, const Camera2D* camera2D)
    {
        m_camera2D = camera2D;
        sheetAnimation.setAnimationRender( m_animatedSprite );

        robot2D::FrameBufferSpecification frameBufferSpecification;
        frameBufferSpecification.attachments =  {
                robot2D::FrameBufferTextureFormat::RGBA8
        };
        frameBufferSpecification.size = windowSize;
        m_frameBuffer = robot2D::FrameBuffer::Create(frameBufferSpecification);

        m_sceneGrid.setup();
    }

    void ViewerView::update(float dt) {
        sheetAnimation.update(dt);
    }

    void ViewerView::beforeRender() {
        m_frameBuffer -> Bind();
    }

    void ViewerView::afterRender() {
        m_frameBuffer -> unBind();
    }

    void ViewerView::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const {
        target.clear(robot2D::Color::White);
        m_sceneGrid.render();

        target.beforeRender();
        target.setView(m_camera2D -> getCameraView());

        target.draw(m_sprite);
    }

    void ViewerView::processImage(const robot2D::vec2f& mousePos, const robot2D::vec2f& windowSize) {
        auto convertedMousePos = m_camera2D -> mapPixelToCoords(mousePos, m_frameBuffer);
        auto&& maskColor = readPixel({convertedMousePos.x, windowSize.y - convertedMousePos.y});
        m_maskColor = maskColor;
        robot2D::Image image{};
        image.create(m_texture.getSize(), m_texture.getPixels(), robot2D::ImageColorFormat::RGBA);
        applyImageMask(image, maskColor);
        m_texture.create(image);
    }

    void ViewerView::onLoadImage(robot2D::Image&& image) {
        m_texture.create(image);

        auto& textureSize = m_texture.getSize();
        m_animatedSprite.setTexture(m_texture, {0, 0,
                                                static_cast<int>(textureSize.x),
                                                static_cast<int>(textureSize.y)});

        auto&& bounds = m_animatedSprite.getGlobalBounds();
        auto windowSize = m_frameBuffer -> getSpecification().size;

        robot2D::vec2f spritePosition = {
                windowSize.x / 2.F - bounds.width / 2.F,
                windowSize.y / 2.F - bounds.height / 2.F
        };

        m_animatedSprite.setPosition(spritePosition);
        m_sprite = m_animatedSprite;
    }

    bool ViewerView::insideView(const robot2D::IntRect& region) const {
        return contains(m_sprite.getGlobalBounds(), region);
    }

    std::pair<bool, robot2D::vec2f> ViewerView::onLoadAnimation(robot2D::Image&& image, const AnimationList& animationList) {
        sheetAnimation.reset();
        m_texture.create(image);

        auto& textureSize = m_texture.getSize();
        m_animatedSprite.setTexture(m_texture, {0, 0,
                                                static_cast<int>(textureSize.x),
                                                static_cast<int>(textureSize.y)});

        auto&& bounds = m_animatedSprite.getGlobalBounds();
        auto windowSize = m_frameBuffer -> getSpecification().size;

        robot2D::vec2f spritePosition = {
                windowSize.x / 2.F - bounds.width / 2.F,
                windowSize.y / 2.F - bounds.height / 2.F
        };

        m_animatedSprite.setPosition(spritePosition);
        m_sprite = m_animatedSprite;
        return {true, spritePosition};
    }

}