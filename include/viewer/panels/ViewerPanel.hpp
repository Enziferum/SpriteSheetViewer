#pragma once

#include <viewer/SpriteSheetAnimation.hpp>
#include "IPanel.hpp"

namespace viewer {


    class ViewerPanel: public IPanel {
    public:
        ViewerPanel();
        ~ViewerPanel() override = default;


        void setSpriteSheetAnimation(SpriteSheetAnimation* spriteSheet);
        void update(float dt) override;
    private:
        SpriteSheetAnimation* m_animation;
    };
}