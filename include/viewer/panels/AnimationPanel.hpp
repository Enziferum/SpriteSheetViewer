#pragma once

#include <viewer/Animation.hpp>
#include <robot2D/Core/MessageBus.hpp>
#include <viewer/MessageDispather.hpp>
#include "IPanel.hpp"
#include "viewer/SpriteSheetAnimation.hpp"

namespace viewer {
    class AnimationPanel: public IPanel {
    public:
        AnimationPanel(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher);
        ~AnimationPanel() override = default;


        void setAnimation(SpriteSheetAnimation* animation);
        void update(float dt) override;
    private:
        void setup();

        void windowFunction();
        void onAdd();
        void onSave();
        void onDelete();
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        SpriteSheetAnimation* m_animation{nullptr};
        std::vector<std::string> m_animationNames{};
        std::string m_currentName;
        std::string m_addName;
        int m_currentAnimation = 0;
        int m_lastCurrentAnimation = -1;
    };

} // namespace viewer