#pragma once

#include <string>
#include "Animation.hpp"

namespace viewer {
    class AnimationIO {
    public:
        AnimationIO() = default;
        ~AnimationIO() = default;

        bool loadFromFile(const std::string& path);
        bool saveToFile(const std::string& path, const AnimationList& animationList,
                        robot2D::vec2f realTexturePos);
    private:
        AnimationList m_animations;
    };
}