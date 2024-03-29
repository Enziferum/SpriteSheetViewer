#pragma once

#include <stack>
#include <queue>
#include <cassert>

#include <robot2D/Util/Logger.hpp>
#include "commands/ICommand.hpp"

namespace viewer {
    class CommandStack {
    public:
        CommandStack() = default;
        ~CommandStack() = default;


        template<typename T, typename ...Args>
        [[maybe_unused]]
        T* addCommand(Args&&... args);

        void addCommand(ICommand::Ptr&& ptr);

        void undo();
        void redo();

        [[nodiscard]]
        bool empty() const noexcept;
    private:
        std::stack<ICommand::Ptr> m_stack {};
        std::queue<ICommand::Ptr> m_redoQueue {};
    };

    template<typename T, typename ...Args>
    T* CommandStack::addCommand(Args&&...args) {
        static_assert(std::is_base_of_v<ICommand, T>);
        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        RB_INFO("Allocate command");
        assert(ptr != nullptr && "Command of Type T is nullptr");
        m_stack.push(ptr);

        return static_cast<T*>(ptr.get());
    }


} // namespace viewer