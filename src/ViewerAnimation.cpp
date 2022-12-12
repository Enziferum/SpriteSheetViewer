#include <robot2D/Graphics/RenderTarget.hpp>
#include <viewer/ViewerAnimation.hpp>

namespace viewer {

    std::pair<bool, int> ViewerAnimation::contains(const robot2D::vec2f& point) {
        for(int i = 0; i < static_cast<int>(m_colliders.size()); ++i)
            if(m_colliders[i].aabb.contains(point))
                return {true, i};
        return {false, -1};
    }

    DebugCollider& ViewerAnimation::operator[](std::size_t index) {
        return m_colliders[index];
    }

    void ViewerAnimation::addFrame(const DebugCollider& collider,
                                   const robot2D::vec2f& worldPosition) {
        m_colliders.emplace_back(collider);
        robot2D::FloatRect convertedFrame {
                collider.aabb.lx - worldPosition.x,
                collider.aabb.ly - worldPosition.y,
                collider.aabb.width,
                collider.aabb.height
        };
        m_animation.addFrame(convertedFrame);
    }

    void ViewerAnimation::eraseFrame(int index) {
        m_colliders.erase(m_colliders.begin() + index);
        m_animation.eraseFrame(index);
    }

    const DebugCollider& ViewerAnimation::operator[](std::size_t index) const {
        return m_colliders[index];
    }

    Animation& ViewerAnimation::getAnimation() {
        return m_animation;
    }

    const Animation& ViewerAnimation::getAnimation() const {
        return m_animation;
    }

    void ViewerAnimation::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const  {
        for(const auto& collider: m_colliders)
            target.draw(collider);
    }

} // namespace viewer