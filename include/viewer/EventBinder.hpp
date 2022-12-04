/*
 Copyright (c) 2022 Alex Raag. All rights reserved.
 Use of this source code is governed by a BSD-style license that can be
 found in the LICENSE file.
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include <robot2D/Core/Event.hpp>

#define BIND_CLASS_FN(fn) [this](auto&& ...args) -> decltype(auto) { \
    this -> fn(std::forward<decltype(args)>(args)...);               \
}

namespace viewer {

    struct EventBinder {
        EventBinder() = default;
        EventBinder(const EventBinder& other) = delete;
        EventBinder& operator=(const EventBinder& other) = delete;
        EventBinder(EventBinder&& other) = delete;
        EventBinder& operator=(EventBinder&& other) = delete;
        ~EventBinder() = default;

        struct IFunc {
            using Ptr = std::shared_ptr<IFunc>;
            virtual ~IFunc() = 0;
            virtual bool execute(const robot2D::Event& event) = 0;
        };

        template<typename F>
        struct Func: IFunc {
            explicit Func(F&& func): m_func{func} {}
            ~Func() override = default;
            F m_func;

            bool execute(const robot2D::Event& event) override {
                m_func(event);
                return true;
            }
        };

        template<typename F>
        void bindEvent(robot2D::Event::EventType eventType, F&& func) {
            auto funcPtr = std::make_shared<Func<F>>(std::forward<F>(func));
            if(!funcPtr)
                return;
            m_events[eventType] = funcPtr;
        }

        void unBind(robot2D::Event::EventType eventType) {
            auto found = m_events.find(eventType);
            if(found == m_events.end())
                return;
            found -> second.reset();
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