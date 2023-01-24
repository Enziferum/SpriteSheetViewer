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

        virtual bool isMouseOver() const { return m_mouseIsOver; }
    protected:
        virtual void checkMouseHover();
        virtual void setMouseHoverDirectly(bool flag) { m_mouseIsOver = flag; }
    protected:
        PanelID m_id;
        bool m_mouseIsOver{false};
    };

}