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
        Animation() = default;
        Animation(std::string title_, int delay_): title{title_}, delay{delay_} {}
        ~Animation() = default;

        void addFrame(const robot2D::FloatRect& frame) {
            frames.emplace_back(frame.as<int>());

            robot2D::IntRect flipRect{
                static_cast<int>(frame.lx + frame.width),
                static_cast<int>(frame.ly),
                static_cast<int>(-frame.width),
                static_cast<int>(frame.height)
            };
            flip_frames.emplace_back(flipRect);
        }

        void eraseFrame(int index) {
            frames.erase(frames.begin() + index);
            flip_frames.erase(flip_frames.begin() + index);
        }

        [[nodiscard]]
        bool valid() const {
            bool a = frames.empty();
            bool b = flip_frames.empty();
            bool res = !a & !b;
            return res;
        }

        void setTitle(const std::string& name) { title = name; }

        std::string title;
        int delay;
        std::vector<robot2D::IntRect> frames;
        std::vector<robot2D::IntRect> flip_frames;
    };

    using AnimationList = std::vector<Animation>;
}

