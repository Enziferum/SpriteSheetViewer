#include <viewer/PanelManager.hpp>

namespace viewer {

    PanelManager::PanelManager(): m_panels{} {}

    void PanelManager::handleEvents(const robot2D::Event& event) {}

    void PanelManager::update(float dt) {
        currDt = dt;
    }

    void PanelManager::render() {
        for(auto& panel: m_panels)
            panel -> update(currDt);
    }

}
