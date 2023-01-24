#include <viewer/SpriteSheet.hpp>
#include "XmlParser.hpp"

namespace viewer {
    SpriteSheet::SpriteSheet():m_animations{} {}

    bool SpriteSheet::loadFromFile(const std::string& path) {
        auto parser = getParser();
        if(!parser || !parser -> loadFromFile(path, m_texturePath, m_animations))
            return false;

        return true;
    }

    bool
    SpriteSheet::saveToFile(const std::string& path,
                    const std::string& texturePath,
                    const robot2D::Color& maskColor,
                    const AnimationList& animationList,
                    robot2D::vec2f realTexturePos) {
        auto parser = getParser();
        if(!parser || !parser -> saveToFile(path, texturePath, maskColor, animationList, realTexturePos))
            return false;

        return true;
    }

} // namespace viewer
