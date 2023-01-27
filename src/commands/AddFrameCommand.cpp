#include <viewer/commands/AddFrameCommand.hpp>

namespace viewer {

    AddFrameCommand::AddFrameCommand(ViewerAnimation& viewerAnimation,
                                     Collider collider):
        m_viewerAnimation{viewerAnimation},
        m_collider{collider}
        {}

    void AddFrameCommand::undo() {
        m_viewerAnimation.eraseLastFrame();
    }

    void AddFrameCommand::redo() {
        m_viewerAnimation.addFrame(m_collider);
    }

} // namespace viewer