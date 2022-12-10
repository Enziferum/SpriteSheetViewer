#pragma once

#include <utility>

#define BIND_CLASS_FN(fn) [this](auto&& ...args) -> decltype(auto) { \
    this -> fn(std::forward<decltype(args)>(args)...);               \
}