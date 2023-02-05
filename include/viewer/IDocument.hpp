#pragma once
#include <memory>

namespace viewer {


    class IDocument {
    public:
        using Ptr = std::shared_ptr<IDocument>;

        virtual ~IDocument() = 0;
        bool& open() { return m_open; }
        bool dirty() const { return m_dirty; }
        bool forceClose() {  }
        bool wantClose() const { return m_wantClose; }
        void setClose(bool flag) { m_wantClose = flag; }

        virtual std::string getName() const = 0;
    protected:
        bool m_open{true};
        bool m_dirty{false};
        bool m_wantClose{false};
    };

}