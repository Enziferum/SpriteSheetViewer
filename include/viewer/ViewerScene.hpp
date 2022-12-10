#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/Sprite.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include <robot2D/Core/MessageBus.hpp>

#include "SpriteSheet.hpp"
#include "PanelManager.hpp"
#include "SpriteSheetAnimation.hpp"
#include "Camera2D.hpp"
#include "DebugCollider.hpp"
#include "EventBinder.hpp"
#include "MessageDispather.hpp"
#include <viewer/Messages.hpp>

namespace viewer {

    class ViewerAnimation: public robot2D::Drawable {
    public:
        ViewerAnimation() = default;
        ~ViewerAnimation() = default;

        std::pair<bool, int> contains(const robot2D::vec2f& point) {
            for(int i = 0; i < m_colliders.size(); ++i)
                if(m_colliders[i].aabb.contains(point))
                    return {true, i};
            return {false, -1};
        }

        DebugCollider& operator[](std::size_t index) {
            return m_colliders[index];
        }

        void addFrame(const DebugCollider& collider, const robot2D::vec2f& worldPosition) {
            m_colliders.emplace_back(collider);
            robot2D::FloatRect convertedFrame{
                    collider.aabb.lx - worldPosition.x,
                    collider.aabb.ly - worldPosition.y,
                    collider.aabb.width,
                    collider.aabb.height
            };
            m_animation.addFrame(convertedFrame);
        }

        void eraseFrame(int index) {
            m_colliders.erase(m_colliders.begin() + index);
            m_animation.eraseFrame(index);
        }

        const DebugCollider& operator[](std::size_t index) const {
            return m_colliders[index];
        }

        Animation& getAnimation() {
            return m_animation;
        }

        const Animation& getAnimation() const {
            return m_animation;
        }

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override {
            for(const auto& collider: m_colliders)
                target.draw(collider);
        }
    private:
        Animation m_animation{};
        std::vector<DebugCollider> m_colliders{};
    };

    class MovableSprite: public robot2D::Drawable {
    public:
        MovableSprite& operator=(const robot2D::Sprite& sprite) {
//            if(m_sprite == sprite)
//                return *this;
            setSprite(sprite);
            return *this;
        }

        void setSprite(const robot2D::Sprite& sprite) {
            m_sprite = sprite;
            auto bounds = m_sprite.getGlobalBounds();
            auto size = m_sprite.getSize();
            debugCollider.aabb = {bounds.lx, bounds.ly, bounds.width, bounds.height};
        }

        void isDrawCollider(bool flag) {}

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates states) const override {
            (void)states;
            //target.draw(debugCollider);
            target.draw(m_sprite);
        }
    private:
        robot2D::Sprite m_sprite;
        DebugCollider debugCollider;
    };

    class ViewerScene {
    public:
        ViewerScene(robot2D::MessageBus& messageBus, MessageDispatcher& dispatcher);
        ViewerScene(const ViewerScene& other) = delete;
        ViewerScene& operator=(const ViewerScene& other) = delete;
        ViewerScene(ViewerScene&& other) = delete;
        ViewerScene& operator=(ViewerScene&& other) = delete;
        ~ViewerScene() = default;

        void setup(robot2D::RenderWindow* window);

        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void render();
    private:
        void onMousePressed(const robot2D::Event& event);
        void onMouseReleased(const robot2D::Event& event);
        void onKeyboardPressed(const robot2D::Event& event);

        void onAddAnimation(const AddAnimationMessage& message);
        void onSwitchAnimation(const SwitchAnimationMessage& message);
        void onDeleteAnimation(const DeleteAnimationMessage& message);

        void setupResources();
        void setupBindings();
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;

        robot2D::RenderWindow* m_window;

        viewer::PanelManager m_panelManager;
        viewer::Camera2D m_camera2D;
        viewer::SpriteSheet m_spriteSheet;
        viewer::SpriteSheetAnimation sheetAnimation;
        EventBinder m_eventBinder;

        robot2D::FrameBuffer::Ptr m_frameBuffer;

        robot2D::Texture m_texture;
        robot2D::Sprite m_animatedSprite;
        MovableSprite m_sprite;


        std::vector<ViewerAnimation> m_animations;
        int m_currentAnimation = -1;

        robot2D::FloatRect movingAABB;
        robot2D::Color selectColor = robot2D::Color::Green;

        bool startedPressed = false;
        int updateAABBit = -1;
    };


}
