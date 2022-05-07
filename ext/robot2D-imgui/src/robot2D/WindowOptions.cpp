#include <robot2D/Extra/WindowOptions.hpp>
#include <imgui/imgui.h>

namespace ImGui {
    WindowOptions::WindowOptions(std::map<int, robot2D::vec2f>&& variables,
                                 std::map<int, robot2D::Color>&& colors):
                                 m_vars{std::move(variables)},
                                 m_colors{std::move(colors)}
                                 {}


    void WindowOptions::enable() const {
        for (const auto &var: m_vars)
            PushStyleVar(var.first, {var.second.x, var.second.y});
        for (const auto &var: m_colors) {
            auto glColor = var.second.toGL();
            PushStyleColor(var.first, ImVec4(glColor.red,
                                             glColor.green,
                                             glColor.blue,
                                             glColor.alpha));
        }
    }

    void WindowOptions::disable() const {
        PopStyleVar(static_cast<int>(m_vars.size()));
        PopStyleColor(static_cast<int>(m_colors.size()));
    }
}