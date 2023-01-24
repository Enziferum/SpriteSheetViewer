#pragma once

#include <string>

namespace viewer {
    std::string openFileDialog(std::string title, std::string filters, std::string directory);
    std::string saveFileDialog(std::string title, std::string filters, std::string directory);
}