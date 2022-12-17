#pragma once

#include <string>
#include <utility>
#include <vector>

#include <robot2D/Graphics/Rect.hpp>
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
        void setAnimations(std::vector<Animation> anims) { m_animations = std::move(anims); }
        const AnimationList& getAnimations() const { return m_animations; }

        Animation* operator[](std::size_t index) {
            if(index >= m_animations.size())
                return nullptr;
            return &m_animations[index];
        }

        void removeAll() {
            m_texturePath = "";
            m_animations.clear();
        }

        bool empty() const {
            if(m_animations.empty())
                return true;
            else
                return !m_animations[0].valid();
        }

        const std::string& getTexturePath() const {return m_texturePath;}
    private:
        std::string m_texturePath;
        std::vector<Animation> m_animations;
    };
} // namespace viewer




