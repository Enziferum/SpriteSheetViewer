#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include <viewer/MessageDispather.hpp>
#include <viewer/SpriteSheetAnimation.hpp>
#include <viewer/Messages.hpp>
#include <viewer/Defines.hpp>

#include "IPanel.hpp"

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
        void showAddAnimationPanel();

        void onAdd();
        void onSave();
        void onDelete();

        void onLoad(const AnimationPanelLoadEmptyMessage& message);
        void onLoadAnimation(const AnimationPanelLoadMessage& message);
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        SpriteSheetAnimation* m_animation{nullptr};
        std::vector<std::string> m_animationNames{};
        std::string m_currentName;
        std::string m_addName;
        int m_currentAnimation = 0;
        int m_lastCurrentAnimation = NO_INDEX;
        bool m_needShowModal{false};
    };

} // namespace viewer