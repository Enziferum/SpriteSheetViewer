#pragma once

#include <string>
#include <vector>
#include <robot2D/Graphics/Rect.hpp>

struct Animation {
    std::string title;
    int delay;
    std::vector<robot2D::IntRect> frames;
    std::vector<robot2D::IntRect> flip_frames;

    bool valid() {
        bool a = frames.empty();
        bool b = frames.empty();
        bool res = !a & !b;
        return res;
    }
};

using AnimationList = std::vector<Animation>;
