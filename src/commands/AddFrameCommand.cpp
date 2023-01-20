#include <viewer/commands/AddFrameCommand.hpp>

namespace viewer {

    AddFrameCommand::AddFrameCommand(ViewerAnimation& viewerAnimation,
                                     Collider debugCollider):
        m_viewerAnimation{viewerAnimation},
        m_debugCollider{debugCollider}
        {

    }

    void AddFrameCommand::undo() {
        m_viewerAnimation.eraseLastFrame();
    }

    void AddFrameCommand::redo() {
        m_viewerAnimation.addFrame(m_debugCollider);
    }

} // namespace viewer