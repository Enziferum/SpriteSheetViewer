#pragma once

#include <viewer/ViewerAnimation.hpp>

#include "ICommand.hpp"

namespace viewer {
    class AddFrameCommand: public ICommand {
    public:
        using Ptr = std::unique_ptr<AddFrameCommand>;

        template<typename ...Args>
        static Ptr create(Args&& ... args) {

        }

        AddFrameCommand(ViewerAnimation& viewerAnimation, DebugCollider debugCollider);
        virtual ~AddFrameCommand() override = default;

        void undo() override;
        void redo() override;
    private:
        ViewerAnimation& m_viewerAnimation;
        DebugCollider m_debugCollider;
    };
} // namespace viewer