#pragma once

#include <robot2D/Core/MessageBus.hpp>

#include <viewer/MessageDispather.hpp>
#include <viewer/SpriteSheetAnimation.hpp>
#include <viewer/Messages.hpp>
#include <viewer/Defines.hpp>
#include <viewer/NamesContainer.hpp>

#include "IPanel.hpp"

namespace viewer {
    class AnimationPanel: public IPanel {
    public:
        AnimationPanel(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher,
                       IAddGetName* namesContainer);
        ~AnimationPanel() override = default;

        void resetNames(const std::vector<std::string>& currentNames) {
           // m_animationNames = currentNames;
            m_currentAnimation = 0;
            m_lastCurrentAnimation = 0;
        }

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
        void onSwitchTab(const SwitchTabMessage& message);
    private:
        robot2D::MessageBus& m_messageBus;
        MessageDispatcher& m_messageDispatcher;
        SpriteSheetAnimation* m_animation{nullptr};
        std::string m_currentName;
        std::string m_addName;
        int m_currentAnimation = NO_INDEX;
        int m_lastCurrentAnimation = NO_INDEX;
        bool m_needShowModal{false};
        IAddGetName* m_namesContainer;
    };

} // namespace viewer