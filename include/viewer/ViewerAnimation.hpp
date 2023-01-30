#pragma once
#include <vector>
#include <robot2D/Graphics/Drawable.hpp>

#include "Animation.hpp"
#include "Collider.hpp"

namespace viewer {
    class ViewerAnimation: public robot2D::Drawable {
    public:
        ViewerAnimation() = default;
        ViewerAnimation(const Animation& animation, const robot2D::vec2f& worldPos = {});
        ~ViewerAnimation() = default;

        std::pair<bool, int> contains(const robot2D::vec2f& point);
        Collider& operator[](std::size_t index);

        void addFrame(const Collider& collider, const robot2D::vec2f& worldPosition);
        void addFrame(const Collider& collider);
        void addFrame(const Collider& collider, std::size_t index);

        std::size_t size() const { return m_animation.frames.size(); }

        void eraseLastFrame();
        void eraseFrame(int index);

        const Collider& operator[](std::size_t index) const;
        Animation& getAnimation();
        const Animation& getAnimation() const;

        void draw(robot2D::RenderTarget& target, robot2D::RenderStates) const override;
    private:
        Animation m_animation{};
        std::vector<Collider> m_colliders{};
        robot2D::vec2f m_worldPos{};
    };

} // namespace viewer