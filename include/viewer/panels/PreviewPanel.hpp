#pragma once

#include "IPanel.hpp"

namespace viewer {
    class PreviewPanel: public IPanel {
    public:
        PreviewPanel();
        ~PreviewPanel() override = default;
    };
} // namespace viewer