#pragma once

#include <viewer/ViewerAnimation.hpp>
#include "ICommand.hpp"

namespace viewer {
    class DeleteFrameCommand: public ICommand {
    public:
        DeleteFrameCommand(ViewerAnimation& viewerAnimation,
                           DebugCollider& debugCollider,
                           std::size_t index);
        ~DeleteFrameCommand() override = default;

        void undo() override;
    private:
        ViewerAnimation& m_viewerAnimation;
        DebugCollider& m_debugCollider;
        std::size_t m_index;
    };
} // namespace viewer