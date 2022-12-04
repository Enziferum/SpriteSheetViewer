#pragma once

#include <cstdint>
#include <memory>
#include <typeindex>

namespace viewer {


    using PanelID = std::type_index;

    class IPanel {
    public:
        using Ptr = std::shared_ptr<IPanel>;
    public:
        IPanel(PanelID panelId);
        virtual ~IPanel() = 0;

        virtual void update(float dt) = 0;
        PanelID getID() const {return m_id;}
    protected:
        PanelID m_id;
    };

}