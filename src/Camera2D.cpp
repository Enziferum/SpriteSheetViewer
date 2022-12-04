#include <viewer/Camera2D.hpp>

namespace viewer {

    Camera2D::Camera2D() {

    }

    void Camera2D::resetViewport(const robot2D::vec2f& viewportSize) {
        m_view.reset({0, 0, viewportSize.x, viewportSize.y});
    }

    void Camera2D::update(float dt) {

    }


}