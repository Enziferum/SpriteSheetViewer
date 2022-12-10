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
#include <algorithm>

namespace profiler {
    namespace stringUtils {

        template <size_t N>
        struct ChangeResult {
            char Data[N];
        };

        template <size_t N, size_t K>
        constexpr auto cleanupOutputString(const char(&expr)[N], const char(&remove)[K])
        {
            ChangeResult<N> result = {};

            size_t srcIndex = 0;
            size_t dstIndex = 0;
            while (srcIndex < N)
            {
                size_t matchIndex = 0;
                while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
                    matchIndex++;
                if (matchIndex == K - 1)
                    srcIndex += matchIndex;
                result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
                srcIndex++;
            }
            return result;
        }
    }
}
