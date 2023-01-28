/*
 Copyright (c) 2023 Alex Raag. All rights reserved.
 Use of this source code is governed by a BSD-style license that can be
 found in the LICENSE file.
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include <robot2D/Core/Event.hpp>

#include "Macro.hpp"

namespace robot2D {
    template<typename T>
    const T& eventAs(const robot2D::Event& event);
}

namespace viewer {

    class EventBinder {
        struct IFunc {
            using Ptr = std::shared_ptr<IFunc>;
            virtual ~IFunc() = 0;
            virtual bool execute(const robot2D::Event& event) = 0;
        };

        template<typename F, typename EventT,
                typename = std::enable_if_t<std::is_invocable_v<F, const EventT&>>
                >
        struct Func: IFunc {
            explicit Func(F&& func): m_func{func} {}
            ~Func() override = default;

            bool execute(const robot2D::Event& event) override {
                const EventT& eventT = robot2D::eventAs<EventT>(event);
                m_func(eventT);
                return true;
            }
        private:
            F m_func;
        };
    public:
        EventBinder() = default;
        EventBinder(const EventBinder& other) = delete;
        EventBinder& operator=(const EventBinder& other) = delete;
        EventBinder(EventBinder&& other) = delete;
        EventBinder& operator=(EventBinder&& other) = delete;
        ~EventBinder() = default;



        template<typename EventT, typename F,
                typename = std::enable_if_t<std::is_invocable_v<F, const EventT&>>>
        [[nodiscard]]
        bool bindEvent(robot2D::Event::EventType eventType, F&& func) {
            auto funcPtr = std::make_shared<Func<F, EventT>>(std::forward<F>(func));
            if(!funcPtr)
                return false;
            m_events[eventType] = funcPtr;
            return true;
        }

        bool unBind(robot2D::Event::EventType eventType) {
            const auto& found = m_events.find(eventType);
            if(found == m_events.end())
                return false;
            m_events.erase(found);
            return true;
        }

        // TODO(a.raag): try to execute not whole event
        void handleEvents(const robot2D::Event& event) {
            if(m_events.find(event.type) != m_events.end())
                m_events[event.type] -> execute(event);
        }
    private:
        std::unordered_map<robot2D::Event::EventType, IFunc::Ptr> m_events{};
    };

} // namespace viewer