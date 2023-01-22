#include <robot2D/Graphics/RenderTarget.hpp>
#include <viewer/ViewerAnimation.hpp>

namespace viewer {

    ViewerAnimation::ViewerAnimation(const Animation& animation,
                                     const robot2D::vec2f& worldPos): m_animation{animation} {
        for(const auto& frame: animation.frames) {
            auto dd = Collider{};
            dd.setRect({worldPos.x + frame.lx, worldPos.y + frame.ly}, {frame.width, frame.height});
            m_colliders.emplace_back(dd);
        }
    }

    std::pair<bool, int> ViewerAnimation::contains(const robot2D::vec2f& point) {
        for(int i = 0; i < static_cast<int>(m_colliders.size()); ++i)
            if(m_colliders[i].contains(point))
                return {true, i};
        return {false, -1};
    }

    Collider& ViewerAnimation::operator[](std::size_t index) {
        return m_colliders[index];
    }

    void ViewerAnimation::addFrame(const Collider& collider,
                                   const robot2D::vec2f& worldPosition) {
        m_worldPos = worldPosition;
        m_colliders.emplace_back(collider);
        const auto& aabb = collider.getRect();

        robot2D::FloatRect convertedFrame {
                aabb.lx - worldPosition.x,
                aabb.ly - worldPosition.y,
                aabb.width,
                aabb.height
        };
        m_animation.addFrame(convertedFrame);
    }

    void ViewerAnimation::eraseFrame(int index) {
        m_colliders.erase(m_colliders.begin() + index);
        m_animation.eraseFrame(index);
    }

    const Collider& ViewerAnimation::operator[](std::size_t index) const {
        return m_colliders[index];
    }

    Animation& ViewerAnimation::getAnimation() {
        return m_animation;
    }

    const Animation& ViewerAnimation::getAnimation() const {
        return m_animation;
    }



    void ViewerAnimation::addFrame(const Collider& collider) {
        m_colliders.emplace_back(collider);
        const auto& aabb = collider.getRect();
        robot2D::FloatRect convertedFrame {
                aabb.lx - m_worldPos.x,
                aabb.ly - m_worldPos.y,
                aabb.width,
                aabb.height
        };
        m_animation.addFrame(convertedFrame);
    }

    void ViewerAnimation::eraseLastFrame() {
        m_animation.frames.pop_back();
        m_animation.flip_frames.pop_back();
        m_colliders.pop_back();
    }

    void ViewerAnimation::addFrame(const Collider& collider, std::size_t index) {
        m_colliders.insert(m_colliders.begin() + index, collider);
        const auto& aabb = collider.getRect();
        robot2D::IntRect convertedFrame {
                aabb.lx - m_worldPos.x,
                aabb.ly - m_worldPos.y,
                aabb.width,
                aabb.height
        };
        m_animation.frames.insert(m_animation.frames.begin() + index, convertedFrame);
        m_animation.flip_frames.insert(m_animation.frames.begin() + index, convertedFrame);
    }

    void ViewerAnimation::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const  {
        for(const auto& collider: m_colliders)
            target.draw(collider);
    }
} // namespace viewer