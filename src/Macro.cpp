#include <stdexcept>
#include <viewer/Macro.hpp>

namespace viewer {

    void throwMessage(std::string&& message, std::string&& file, int line) {
        std::string full =
                std::string{file} + ":" + std::to_string(line) + " " + message;
        throw std::runtime_error(full.c_str());
    }

} // namespace viewer