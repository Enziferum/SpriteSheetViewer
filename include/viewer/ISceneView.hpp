#pragma once

#include <robot2D/Graphics/Image.hpp>
#include "ViewerAnimation.hpp"

namespace viewer {

    class ISceneView {
    public:
        virtual ~ISceneView() = 0;
        virtual void updateView(std::size_t tabIndex, ViewerAnimation* animation) = 0;
        virtual void onLoadImage(robot2D::Image&& image, std::size_t newIndex) = 0;
        virtual std::pair<bool, robot2D::vec2f> onLoadAnimation(robot2D::Image&& image) = 0;
        virtual void resetNames(const std::vector<std::string>& names) = 0;
        virtual robot2D::Color getImageMaskColor() const = 0;
    };

} // namespace viewer