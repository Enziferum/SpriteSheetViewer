#pragma once

#include <robot2D/Graphics/RenderWindow.hpp>
#include <robot2D/Graphics/Sprite.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>
#include <robot2D/Core/MessageBus.hpp>

#include "SpriteSheet.hpp"
#include "PanelManager.hpp"
#include "SpriteSheetAnimation.hpp"
#include "Camera2D.hpp"

#include "EventBinder.hpp"
#include "MessageDispather.hpp"
#include "Messages.hpp"
#include "ViewerAnimation.hpp"
#include "SceneGrid.hpp"

namespace viewer {

    class MovableSprite: public robot2D::Drawable {
    public:
        MovableSprite& operator=(const robot2D::Sprite& sprite) {
//            if(m_sprite == sprite)
//                return *this;
            setSprite(sprite);
            return *this;
        }

        void setPosition(const robot2D::vec2f& position) {
            m_sprite.setPosition(position);
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
        void onSaveAnimations(const SaveAnimationsMessage& message);

        void onLoadImage(const LoadImageMessage& message);
        void onLoadXml(const LoadXmlMessage& message);

        void setupResources();
        void setupBindings();
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;

        robot2D::RenderWindow* m_window;

        PanelManager m_panelManager;
        Camera2D m_camera2D;
        SpriteSheet m_spriteSheet;
        SpriteSheetAnimation sheetAnimation;
        EventBinder m_eventBinder;

        SceneGrid m_sceneGrid;

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


} // namespace viewer
