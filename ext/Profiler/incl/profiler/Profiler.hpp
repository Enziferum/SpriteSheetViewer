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

#include "Timer.hpp"
#include "ProfilerManager.hpp"
#include "Utils.hpp"

#define PROFILER_DEBUG 1
#if PROFILER_DEBUG
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) \
    || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define RB_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define RB_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define RB_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define RB_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define RB_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define RB_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define RB_FUNC_SIG __func__
	#else
		#define HZ_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif

    #define PROFILE_BEGIN(name, path) profiler::ProfilerManager::get().begin(name, path);
    #define PROFILE_END() profiler::ProfilerManager::get().end();
    #define PROFILE_BACKEND(name, line) constexpr auto fixedName##line = ::profiler::stringUtils::cleanupOutputString(name, "__cdecl ");\
    ::profiler::Timer timer##line(fixedName##line.Data)
    #define PROFILE_LINE(name, line) PROFILE_BACKEND(name, line)
    #define PROFILE_SCOPE(name) PROFILE_LINE(name, __LINE__)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(RB_FUNC_SIG)
#else
    #define PROFILE_BEGIN(name, path)
    #define PROFILE_END()
    #define PROFILE_SCOPE(name)
    #define PROFILE_FUNCTION()
#endif