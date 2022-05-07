#pragma once

#include <string>
#include <utility>
#include <vector>

#include <robot2D/Graphics/Rect.hpp>

struct Animation {
    std::string title;
    int delay;
    std::vector<robot2D::IntRect> frames;
    std::vector<robot2D::IntRect> flip_frames;
};

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
private:
    std::vector<Animation> animations;
};


