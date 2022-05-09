#pragma once

#include <string>
#include <utility>
#include <vector>

#include <robot2D/Graphics/Rect.hpp>

#include "Animation.hpp"

enum class LoaderType {
    SpriteDecomposer,
    Engine,
    Custom
};

class SpriteSheet {
public:
    SpriteSheet();
    ~SpriteSheet() = default;

    bool loadFromFile(const std::string& path);
    void setAnimations(std::vector<Animation> anims) { animations = std::move(anims); }
    const std::vector<Animation>& getAnimations() const { return animations; }

    Animation* getAnimation(std::size_t index) {
        if(index >= animations.size())
            return nullptr;
        return &animations[index];
    }

    bool empty() {
        if(animations.empty())
            return true;
        else
            return !animations[0].valid();
    }
private:
    std::vector<Animation> animations;
};


