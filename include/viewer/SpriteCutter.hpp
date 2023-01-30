#pragma once

#include <vector>
#include <set>

#include <robot2D/Graphics/Texture.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Color.hpp>

namespace viewer {
    class SpriteCutter {
    public:
        using colorPoint = std::pair<robot2D::Color, robot2D::vec2i>;
        SpriteCutter() = default;
        ~SpriteCutter() = default;

        std::vector<robot2D::IntRect> cutFrames(const robot2D::UIntRect& clipRegion, robot2D::Image& image,
                                                robot2D::vec2f worldPosition);
    private:

        std::vector<std::vector<colorPoint>> packColorMap(const robot2D::UIntRect& clipRegion,
                                                          robot2D::Image& image,
                                                          robot2D::vec2f worldPosition);

        std::vector<robot2D::vec2i> getNeighbors(robot2D::vec2i point, robot2D::Image& image);

        robot2D::IntRect splitPoints(std::set<robot2D::vec2i>& points);

        robot2D::Color getColor(robot2D::Image& image, robot2D::vec2i position);

        robot2D::IntRect findBoundingBox(robot2D::Image& image, robot2D::vec2i point);

        void eraseSprite(robot2D::Image& image, robot2D::IntRect rect);

        std::vector<robot2D::IntRect> filterInsideFrames(std::vector<robot2D::IntRect> frames);

        std::pair<std::vector<robot2D::IntRect>, bool> mergeOverlappingFrames(std::vector<robot2D::IntRect> frames);
    };

}