#pragma once

#include <robot2D/Graphics/Sprite.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>

#include "SpriteSheetAnimation.hpp"
#include "MovableSprite.hpp"
#include "SceneGrid.hpp"
#include "Messages.hpp"
#include "Camera2D.hpp"

namespace viewer {
    class ViewerView: public robot2D::Drawable {
    public:
        ViewerView() = default;
        ~ViewerView() override = default;

        void setup(const robot2D::vec2i& windowSize, const Camera2D* camera2D);
        void update(float dt);
        void beforeRender();
        void afterRender();

        void processImage(const robot2D::vec2f& mousePos, const robot2D::vec2f& windowSize);
        void flipAnimation(bool flag) {
            sheetAnimation.reset();
            sheetAnimation.setFlip(flag);
        }

        SpriteSheetAnimation* getAnimation() {
            return &sheetAnimation;
        }
        robot2D::FrameBuffer::Ptr getFrameBuffer() const { return m_frameBuffer; }
        robot2D::vec2f getPosition() { return m_animatedSprite.getPosition(); }
        robot2D::Color getImageMaskColor()const { return m_maskColor; }
        robot2D::Image& getImage() { return m_texture.getImage(); }


        void onLoadImage(robot2D::Image&& image);
        std::pair<bool, robot2D::vec2f> onLoadAnimation(robot2D::Image&& image);
        bool insideView(const robot2D::IntRect& region) const;
        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        SpriteSheetAnimation sheetAnimation;
        robot2D::FrameBuffer::Ptr m_frameBuffer;
        robot2D::Texture m_texture;
        robot2D::Sprite m_animatedSprite;
        MovableSprite m_sprite;
        SceneGrid m_sceneGrid;
        robot2D::Color m_maskColor;
        const Camera2D* m_camera2D{nullptr};
    };
}