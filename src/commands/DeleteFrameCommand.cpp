#include <utility>
#include <viewer/commands/DeleteFrameCommand.hpp>

namespace viewer {
    DeleteFrameCommand::DeleteFrameCommand(
            ViewerAnimation& viewerAnimation,
            Collider collider,
            std::size_t index):
            m_viewerAnimation{viewerAnimation},
            m_collider{collider},
            m_index{index}{}

    void DeleteFrameCommand::undo() {
        m_viewerAnimation.addFrame(m_collider, m_index);
    }

    void DeleteFrameCommand::redo() {
       m_viewerAnimation.addFrame(m_collider, m_index);
    }
} // namespace viewer