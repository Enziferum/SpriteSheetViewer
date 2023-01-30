#pragma once

#include <viewer/ViewerAnimation.hpp>
#include "ICommand.hpp"

namespace viewer {
    class DeleteFrameCommand: public ICommand {
    public:
        DeleteFrameCommand(ViewerAnimation& viewerAnimation,
                           Collider collider,
                           std::size_t index);
        ~DeleteFrameCommand() override = default;

        void undo() override;
        void redo() override;
    private:
        ViewerAnimation& m_viewerAnimation;
        Collider m_collider;
        std::size_t m_index;
    };
} // namespace viewer