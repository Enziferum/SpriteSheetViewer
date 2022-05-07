#pragma once

#include <memory>
#include <unordered_map>
#include <robot2D/Core/Event.hpp>
#include "Panels.hpp"

class PanelManager {
public:
    PanelManager();
    ~PanelManager() = default;

    template<typename T, typename ...Args>
    bool addPanel(const PanelID& id, Args&& ...args);

    template<typename T>
    T* getPanel(const PanelID& id);

    bool addPanel(const PanelID& id, IPanel::Ptr ptr);
    void handleEvents(const robot2D::Event& event);
    void update(float dt);
    void render();
private:
    std::unordered_map<PanelID, IPanel::Ptr> m_panels;
    float currDt = 0.f;
};

template<typename T, typename... Args>
bool PanelManager::addPanel(const PanelID& id, Args&&... args) {
    if(!std::is_base_of<IPanel, T>::value)
        return false;
    return m_panels.emplace(id, std::make_shared<T>(std::forward<Args>(args)...)).second;
}

template<typename T>
T* PanelManager::getPanel(const PanelID& id) {
    if(!std::is_base_of<IPanel, T>::value)
        return nullptr;
    auto it = m_panels.find(id);
    if(it == m_panels.end())
        return nullptr;
    return dynamic_cast<T*>(it->second.get());
}

