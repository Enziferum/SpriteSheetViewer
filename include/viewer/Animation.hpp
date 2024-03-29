/*
 Copyright (c) 2022 Alex Raag. All rights reserved.
 Use of this source code is governed by a BSD-style license that can be
 found in the LICENSE file.
*/

#pragma once

#include <string>
#include <vector>

#include <robot2D/Graphics/Rect.hpp>

namespace viewer {
    struct Animation {
        Animation() {}
        Animation(std::string title_, int delay_): title{title_}, delay{delay_} {}
        ~Animation() = default;

        void addFrame(const robot2D::FloatRect& frame) {
            frames.emplace_back(robot2D::IntRect {frame.lx, frame.ly, frame.width, frame.height});
            flip_frames.emplace_back(robot2D::IntRect{frame.lx + frame.width,
                                                      frame.ly, -frame.width,
                                                      frame.height});
        }

        void eraseFrame(int index) {
            frames.erase(frames.begin() + index);
            flip_frames.erase(flip_frames.begin() + index);
        }

        bool valid() const {
            bool a = frames.empty();
            bool b = flip_frames.empty();
            bool res = !a & !b;
            return res;
        }

        std::string title;
        int delay;
        std::vector<robot2D::IntRect> frames;
        std::vector<robot2D::IntRect> flip_frames;
    };

    using AnimationList = std::vector<Animation>;
}

