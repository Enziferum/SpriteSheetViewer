#pragma once

#include <viewer/SpriteSheetAnimation.hpp>
#include "IPanel.hpp"

namespace viewer {


    class ViewerPanel: public IPanel {
    public:
        ViewerPanel();
        ~ViewerPanel() override = default;

        bool isMouseOver() const override { return m_isMouseOver; }
        void setSpriteSheetAnimation(SpriteSheetAnimation* spriteSheet);
        SpriteSheetAnimation* getSpriteSheetAnimation() const { return m_animation; }
        void update(float dt) override;
    private:
        SpriteSheetAnimation* m_animation;
        bool m_isMouseOver{false};
    };
}