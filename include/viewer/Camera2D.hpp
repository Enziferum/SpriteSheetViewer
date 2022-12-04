#pragma once

#include <robot2D/Graphics/View.hpp>

namespace viewer {

    class Camera2D {
    public:
        Camera2D();
        Camera2D(const Camera2D& other) = delete;
        Camera2D& operator=(const Camera2D& other) = delete;
        Camera2D(Camera2D&& other) = delete;
        Camera2D& operator=(Camera2D&& other) = delete;
        ~Camera2D() = default;

        void resetViewport(const robot2D::vec2f& viewportSize);
        void update(float dt);

        const robot2D::View& getView() const {
            return m_view;
        }
    private:
        robot2D::View m_view{};
    };
}