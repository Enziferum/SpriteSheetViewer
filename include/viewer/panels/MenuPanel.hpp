#pragma once

#include <robot2D/Core/MessageBus.hpp>
#include <viewer/SpriteSheetAnimation.hpp>
#include "IPanel.hpp"

namespace viewer {
    class MenuPanel: public IPanel {
    public:
        MenuPanel(robot2D::MessageBus& messageBus);
        ~MenuPanel() override = default;

        void update(float dt) override;
        void setSpriteSheetAnimation(const SpriteSheetAnimation* spriteSheet) {
            m_animation = spriteSheet;
        }
    private:
        void showFileMenu();
    private:
        robot2D::MessageBus& m_messageBus;
        const SpriteSheetAnimation* m_animation;
    };
}