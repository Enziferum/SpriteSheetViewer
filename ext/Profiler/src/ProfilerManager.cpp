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
#include <iostream>
#include <profiler/ProfilerManager.hpp>
#include <profiler/ThreadUtils.hpp>

namespace profiler {

    ProfilerManager::ProfilerManager(): m_session{nullptr},
    m_threadConverter{} {}

    ProfilerManager::~ProfilerManager() {
        endSession();
    }

    ProfilerManager& ProfilerManager::get() {
        static ProfilerManager profiler;
        return profiler;
    }


    void ProfilerManager::begin(const std::string& name, const std::string& path) {
        LOCK(m_mutex)
        m_threadConverter.getIndex(std::this_thread::get_id());
        if (m_session)
        {
            // If there is already a current session, then close it before beginning new one.
            // Subsequent profiling output meant for the original session will end up in the
            // newly opened session instead.  That's better than having badly formatted
            // profiling output.
            std::cerr << "Already have active session, 1 session per Project" << std::endl;
            endSession();
        }
        m_outputStream.open(path);

        if (m_outputStream.is_open())
        {
            m_session = std::make_unique<ProfileSession>();
            writeHeader();
        }
        else
        {
            std::cerr << "Can't open outputStream" << std::endl;
        }
    }

    void ProfilerManager::end() {
        LOCK(m_mutex)
        endSession();
    }

    void ProfilerManager::writeHeader() {
        m_outputStream << "{\"otherData\": {}, \n \"traceEvents\":[{}";
        m_outputStream.flush();
    }


    void ProfilerManager::writeResult(const ProfileResult& result) {
        std::stringstream json;

        json << std::setprecision(3) << std::fixed;
        json << ",{  \n ";
        json << "\"cat\":\"function\",";
        json << "\"dur\":" << (result.elapsedTime.count()) << ',';
        json << "\"name\":\"" << result.name << "\",";
        json << "\"ph\":\"X\",";
        json << "\"pid\":0,";
        // mainThreadID = 0
        if(m_threadConverter.getIndex(result.threadID) == 0)
            json << "\"tid\":\"" << "Main Thread" << "\",";
        else
            json << "\"tid\":\"" << "Thread " + std::to_string(m_threadConverter.getIndex(result.threadID))
            << "\",";
        json << "\"ts\":" << result.start.count();
        json << "}";

        LOCK(m_mutex)
        if (m_session)
        {
            m_outputStream << json.str();
            m_outputStream.flush();
        }
    }

    void ProfilerManager::writeFooter() {
        m_outputStream << "\n ]}";
        m_outputStream.flush();
    }

    void ProfilerManager::endSession() {
        writeFooter();
        m_outputStream.close();
    }

}

