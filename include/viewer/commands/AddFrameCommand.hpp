#pragma once

#include <viewer/ViewerAnimation.hpp>

#include "ICommand.hpp"

namespace viewer {
    class AddFrameCommand: public ICommand {
    public:
        AddFrameCommand(ViewerAnimation& viewerAnimation, Collider debugCollider);
        virtual ~AddFrameCommand() override = default;

        void undo() override;
        void redo() override;
    private:
        ViewerAnimation& m_viewerAnimation;
        Collider m_debugCollider;
    };
} // namespace viewer