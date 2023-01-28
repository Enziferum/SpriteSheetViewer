#pragma once

#include <utility>
#include <string>

namespace viewer {
    #define BIND_CLASS_FN(fn) [this](auto&& ...args) -> decltype(auto) \
    {                                                                  \
        this -> fn(std::forward<decltype(args)>(args)...);             \
    }

    void throwMessage(std::string&& message, std::string&& file, int line);

    #define THROW(message) throwMessage(message, __FILE__, __LINE__)

} // namespace viewer