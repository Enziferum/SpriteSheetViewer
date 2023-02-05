#include <cassert>
#include <viewer/TabContainer.hpp>

namespace viewer {
    IDocument::~IDocument() {}

    ViewerAnimation& TabContainer::addAnimation(ViewerAnimation&& viewerAnimation) {
        m_dirty = true;
        return m_animations.emplace_back(viewerAnimation);
    }

    void TabContainer::eraseAnimation(std::size_t index) {
        m_dirty = true;
        assert(index < m_animations.size());
        m_animations.erase(m_animations.begin() + index);
    }

    void TabContainer::clearAnimations() {
        m_animations.clear();
    }

    std::size_t TabContainer::getSize() const noexcept {
        return m_animations.size();
    }

    const std::vector<ViewerAnimation>& TabContainer::getAnimations() const {
        return m_animations;
    }

    std::vector<ViewerAnimation>& TabContainer::getAnimations() {
        return m_animations;
    }

    ViewerAnimation& TabContainer::addAnimation(const Animation& animation, const robot2D::vec2f& worldPos) {
        m_dirty = true;
        ViewerAnimation viewerAnimation{animation, worldPos};
        m_animations.emplace_back(viewerAnimation);
        return m_animations.back();
    }

    ViewerAnimation& TabContainer::operator[](std::size_t index) {
        return m_animations[index];
    }

    const ViewerAnimation& TabContainer::operator[](std::size_t index) const {
        return m_animations[index];
    }

    void TabContainer::setTexturePath(std::string path) { m_texturePath = path; }
    const std::string& TabContainer::getTexturePath() const { return m_texturePath; }
} // namespace viewer