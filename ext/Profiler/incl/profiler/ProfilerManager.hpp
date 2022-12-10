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

#pragma once

#include <string>
#include <sstream>
#include <mutex>
#include <fstream>

#include "ProfileResult.hpp"
#include "ThreadConverter.hpp"

namespace profiler {

    struct ProfileSession {
        using Ptr = std::unique_ptr<ProfileSession>;
        std::string name;
    };


    class ProfilerManager {
    public:
        ProfilerManager(const ProfilerManager&) = delete;
        ProfilerManager& operator=(const ProfilerManager&) = delete;

        void begin(const std::string& name, const std::string& path);
        void end();

        void writeResult(const ProfileResult& result);
        static ProfilerManager& get();
    private:
        ProfilerManager();
        ~ProfilerManager();

        void writeHeader();
        void writeFooter();
        void endSession();
    private:
        std::mutex m_mutex;
        std::ofstream m_outputStream;
        ProfileSession::Ptr m_session;
        ThreadConverter m_threadConverter;
    };

}




