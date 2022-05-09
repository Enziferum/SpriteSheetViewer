#include "viewer/PanelManager.hpp"

PanelManager::PanelManager():
m_panels() {}

bool PanelManager::addPanel(const PanelID& id, IPanel::Ptr ptr) {
    return m_panels.emplace(id, ptr).second;
}

void PanelManager::handleEvents(const robot2D::Event& event) {

}

void PanelManager::update(float dt) {

}

void PanelManager::render() {
    for(auto& it: m_panels){
        it.second->update(0.f);
    }
}
