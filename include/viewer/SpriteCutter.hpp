#pragma once

#include <vector>
#include <set>

#include <robot2D/Graphics/Texture.hpp>
#include <robot2D/Graphics/Rect.hpp>
#include <robot2D/Graphics/Color.hpp>

namespace viewer {
    struct ColorPoint {
        bool opaque;
        robot2D::vec2i pos;

        explicit operator bool() const noexcept {
            return opaque;
        }
    };

    using visitMatrix = std::vector<std::vector<int>>;
    using colorPointMatrix = std::vector<std::vector<ColorPoint>>;

    class SpriteCutter {
    public:
        using colorPoint = std::pair<robot2D::Color, robot2D::vec2i>;
        SpriteCutter() = default;
        ~SpriteCutter() = default;

        std::vector<robot2D::IntRect> cutFrames(const robot2D::UIntRect& clipRegion, robot2D::Image& image,
                                                robot2D::vec2f worldPosition);
    private:
        bool isSafe(const colorPointMatrix& M, int row, int col, visitMatrix& visited);
        void dfs(const colorPointMatrix& M, int row, int col, visitMatrix& visited,
                 std::vector<robot2D::vec2i>& points);
    };

}