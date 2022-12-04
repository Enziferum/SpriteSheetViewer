#pragma once

#include <memory>
#include <unordered_map>
#include <algorithm>

#include <robot2D/Core/Event.hpp>
#include <viewer/panels/IPanel.hpp>

namespace viewer {
    class PanelManager {
    public:
        PanelManager();
        ~PanelManager() = default;

        template<typename T, typename ...Args>
        T& addPanel(Args&& ...args);

        template<typename T>
        T& getPanel();

        void handleEvents(const robot2D::Event& event);
        void update(float dt);
        void render();
    private:
        using PanelID = std::type_index;
        std::vector<IPanel::Ptr> m_panels;
        float currDt = 0.f;
    };

    template<typename T, typename... Args>
    T& PanelManager::addPanel(Args&&... args) {
        static_assert(std::is_base_of<IPanel, T>::value && "Adding T, must be IPanel child");
        m_panels.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
        return *(dynamic_cast<T*>(m_panels.back().get()));
    }

    template<typename T>
    T& PanelManager::getPanel() {
        PanelID uniqueType(typeid(T));
        auto found = std::find_if(m_panels.begin(), m_panels.end(), [uniqueType](const IPanel::Ptr& ptr) {
            return ptr -> getID() == uniqueType;
        });

        assert(found != m_panels.end() && "Panel must be added before using");

        return *(static_cast<T*>(found -> get()));
    }
}


