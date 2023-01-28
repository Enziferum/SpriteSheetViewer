#pragma once

#include <string>
#include <robot2D/Graphics/Color.hpp>
#include <viewer/Animation.hpp>

namespace viewer {
    class IParser {
    public:
        virtual ~IParser() = 0;
        virtual bool loadFromFile(const std::string& path, std::string& texturePath, AnimationList& animations) = 0;
        virtual bool saveToFile(const std::string& path,
                                const std::string& texturePath,
                                const robot2D::Color& maskColor,
                                const AnimationList& animationList,
                                robot2D::vec2f realTexturePos) = 0;
    };

    std::unique_ptr<IParser> getParser();
} // namespace viewer