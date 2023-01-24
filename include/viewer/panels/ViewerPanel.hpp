#pragma once

#include <viewer/SpriteSheetAnimation.hpp>
#include "IPanel.hpp"

namespace viewer {


    class ViewerPanel: public IPanel {
    public:
        ViewerPanel();
        ~ViewerPanel() override = default;

        void setSpriteSheetAnimation(SpriteSheetAnimation* spriteSheet);
        SpriteSheetAnimation* getSpriteSheetAnimation() const { return m_animation; }
        void update(float dt) override;
    private:
        void guiUpdate();
    private:
        SpriteSheetAnimation* m_animation;
    };
}