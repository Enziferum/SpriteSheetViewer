#pragma once

#include <string>

namespace viewer {
    std::string openFileDialog(std::string title, std::string filters, std::string directory);
    std::string saveFileDialog(const std::string& title, const std::string& filters);
}