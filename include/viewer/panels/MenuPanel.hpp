#pragma once

#include <viewer/SpriteSheetAnimation.hpp>
#include "IPanel.hpp"

namespace viewer {
    class MenuPanel: public IPanel {
    public:
        MenuPanel();
        ~MenuPanel() override = default;

        void update(float dt) override;
        void setSpriteSheetAnimation(const SpriteSheetAnimation* spriteSheet) {
            m_animation = spriteSheet;
        }
    private:
        void showFileMenu();
        const SpriteSheetAnimation* m_animation;
    };
}