#pragma once
#include <vector>
#include <robot2D/Graphics/Drawable.hpp>

#include "Animation.hpp"
#include "DebugCollider.hpp"

namespace viewer {
    class ViewerAnimation: public robot2D::Drawable {
    public:
        ViewerAnimation() = default;
        ViewerAnimation(const Animation& animation, const robot2D::vec2f& worldPos = {});
        ~ViewerAnimation() = default;

        std::pair<bool, int> contains(const robot2D::vec2f& point);
        DebugCollider& operator[](std::size_t index);

        void addFrame(const DebugCollider& collider, const robot2D::vec2f& worldPosition);
        void eraseFrame(int index);

        const DebugCollider& operator[](std::size_t index) const;
        Animation& getAnimation();
        const Animation& getAnimation() const;

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        Animation m_animation{};
        std::vector<DebugCollider> m_colliders{};
    };

} // namespace viewer