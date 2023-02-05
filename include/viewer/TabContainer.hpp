#pragma once
#include <vector>
#include "ViewerAnimation.hpp"
#include "IDocument.hpp"

namespace viewer {

    class TabContainer: public IDocument {
    public:
        using Ptr = std::shared_ptr<TabContainer>;

        TabContainer() = default;
        ~TabContainer() override = default;

        ViewerAnimation& addAnimation(const Animation& animation, const robot2D::vec2f& worldPos = {});
        ViewerAnimation& operator[](std::size_t index);
        const ViewerAnimation& operator[](std::size_t index) const;
        ViewerAnimation& addAnimation(ViewerAnimation&& viewerAnimation) ;

        void eraseAnimation(std::size_t index);
        void clearAnimations();

        std::size_t getSize() const noexcept;
        const std::vector<ViewerAnimation>& getAnimations() const;
        std::vector<ViewerAnimation>& getAnimations();


        void setTexturePath(std::string path);
        const std::string& getTexturePath() const;

        std::string getName() const override { return ""; }
    private:
        std::vector<ViewerAnimation> m_animations;
        std::string m_texturePath;
    };
} // namespace viewer