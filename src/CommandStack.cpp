#include <viewer/CommandStack.hpp>

namespace viewer {

    void CommandStack::undo() {
        if(m_stack.empty())
            return;

        auto ptr = m_stack.top();
        m_stack.pop();

        ptr -> undo();
        m_redoQueue.push(ptr);
    }

    void CommandStack::redo() {
        if(m_redoQueue.empty())
            return;

        auto ptr = m_redoQueue.front();
        m_redoQueue.pop();

        ptr -> redo();
    }

    bool CommandStack::empty() const noexcept {
        return m_stack.empty();
    }

    void CommandStack::addCommand(ICommand::Ptr&& ptr) {
        assert(ptr != nullptr && "Don't add nullptr command");
        m_stack.push(std::move(ptr));
    }
} // namespace viewer