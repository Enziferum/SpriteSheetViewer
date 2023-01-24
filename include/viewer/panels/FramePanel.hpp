#pragma once

#include "IPanel.hpp"

namespace viewer {
    class FramePanel: public IPanel {
    public:
        FramePanel();
        ~FramePanel() override = default;

        void update(float dt) override;
    };
} // namespace viewer