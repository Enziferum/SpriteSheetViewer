/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
Profiler - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/
#include <profiler/Timer.hpp>
#include <profiler/ProfilerManager.hpp>

namespace profiler {

    Timer::Timer(const std::string& name): m_name(name), m_stopped(false) {
        m_startPoint = std::chrono::steady_clock::now();
    }

    Timer::~Timer() {
        if(!m_stopped)
            stop();
    }

    void Timer::stop() {
        auto endTimepoint = std::chrono::steady_clock::now();
        auto highResStart = pointMicroseconds { m_startPoint.time_since_epoch() };
        auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch()
                - std::chrono::time_point_cast<std::chrono::microseconds>(m_startPoint).time_since_epoch();
        ProfilerManager::get().writeResult({m_name, highResStart, elapsedTime, std::this_thread::get_id()});
    }
}
