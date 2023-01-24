#pragma once

#include <string>
#include <utility>
#include <vector>

#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Color.hpp>
#include "Animation.hpp"

namespace viewer {
    enum class LoaderType {
        SpriteDecomposer,
        Engine,
        Custom
    };

    class SpriteSheet final {
    public:
        SpriteSheet();
        ~SpriteSheet() = default;

        bool loadFromFile(const std::string& path);
        bool saveToFile(const std::string& path,
                        const std::string& texturePath,
                        const robot2D::Color& maskColor,
                        const AnimationList& animationList,
                        robot2D::vec2f realTexturePos = {});

        const AnimationList& getAnimations() const { return m_animations; }

        Animation* operator[](std::size_t index) {
            if(index >= m_animations.size())
                return nullptr;
            return &m_animations[index];
        }

        bool empty() const {
            if(m_animations.empty())
                return true;
            else
                return !m_animations[0].valid();
        }

        const std::string& getTexturePath() const { return m_texturePath; }
    private:
        std::string m_texturePath;
        std::vector<Animation> m_animations;
    };
} // namespace viewer




