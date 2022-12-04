#pragma once

#include <atomic>
#include <mutex>
#include <memory>
#include <queue>

namespace viewer {
    template<typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue();
        ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue& other);
        ThreadSafeQueue(ThreadSafeQueue&& other);
        ThreadSafeQueue& operator=(ThreadSafeQueue&& other);
        ~ThreadSafeQueue();

        bool empty() const noexcept;

    private:
        // TODO @a.raag set mem to relaxed
        std::atomic_bool m_running;

        std::queue<T> m_queue;
    };
}