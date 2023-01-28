#include <viewer/Quad.hpp>

namespace viewer {
    robot2D::FloatRect Quad::getFrame() const {
        return {position.x, position.y, size.x, size.y};
    }

    void Quad::draw(robot2D::RenderTarget& target,
              robot2D::RenderStates states) const {
        robot2D::Transform transform;
        transform.translate(position);
        transform.scale(size);

        states.transform *= transform;
        states.color = color;
        states.texture = texture;
        target.draw(states);
    }
    
} // namespace viewer