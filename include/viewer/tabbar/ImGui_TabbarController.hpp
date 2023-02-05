#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <imgui/imgui.h>

namespace robot2D {

    struct TabBarItem {
        std::string name;
        bool open{true};
        int flags;
    };

    class ImGui_TabBarControllerDelegate {
    public:
        virtual ~ImGui_TabBarControllerDelegate() = 0;
        virtual void switchIndex(std::size_t index) = 0;
    };

    class ImGui_TabBarController {
    public:
        ImGui_TabBarController(std::string internalName);
        virtual ~ImGui_TabBarController();

        void addTab(const TabBarItem& tabBarItem);
        virtual void setupController();

        void setDelegate(ImGui_TabBarControllerDelegate* delegate) { m_delegate = delegate; }
        void setVisibleRenderCallback(std::function<void()>&& callback) { m_renderCallback = std::move(callback); }

        /// your logic here ///
        virtual void startTabRender(bool visible, int tabIndex);
        virtual void finishTabRender(bool visible, int tabIndex);
        virtual void postRender();
        void render();
    protected:
        std::vector<TabBarItem> m_items;
        std::string m_internalName;
        std::unordered_map<int, bool> m_tabIndices;

        std::function<void()> m_renderCallback;

        /// mem leak ??
        ImGui_TabBarControllerDelegate* m_delegate{nullptr};

        ImGuiTabBarFlags m_flags{0};
        int m_lastOpenIndex{0};
        bool m_reordable{false};
    };
}