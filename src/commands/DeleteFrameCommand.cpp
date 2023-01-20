#include <utility>
#include <viewer/commands/DeleteFrameCommand.hpp>

namespace viewer {
    DeleteFrameCommand::DeleteFrameCommand(
            ViewerAnimation& viewerAnimation,
            Collider debugCollider,
            std::size_t index):
            m_viewerAnimation{viewerAnimation},
            m_debugCollider{debugCollider},
            m_index{index}{}

    void DeleteFrameCommand::undo() {
        m_viewerAnimation.addFrame(m_debugCollider, m_index);
    }

    void DeleteFrameCommand::redo() {
       // m_viewerAnimation.addFrame(m_debugCollider, m_index);
    }
} // namespace viewer