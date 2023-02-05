#include <viewer/tabbar/ImGui_TabbarController.hpp>

namespace robot2D {
    ImGui_TabBarControllerDelegate::~ImGui_TabBarControllerDelegate() {}

    ImGui_TabBarController::ImGui_TabBarController(std::string internalName):
        m_internalName(internalName) {}

    ImGui_TabBarController::~ImGui_TabBarController() {}

    void ImGui_TabBarController::addTab(const TabBarItem& tabBarItem) {
        m_items.emplace_back(tabBarItem);
    }

    void ImGui_TabBarController::startTabRender(bool visible, int tabIndex) {}

    void ImGui_TabBarController::finishTabRender(bool visible, int tabIndex) {}

    void ImGui_TabBarController::setupController() {}

    void ImGui_TabBarController::postRender() {

    }


    void ImGui_TabBarController::render() {
        static bool opt_reorderable = false;
        static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;
        ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);

        if (ImGui::BeginTabBar(m_internalName.c_str(), tab_bar_flags))
        {
            for(int i = 0; i < static_cast<int>(m_items.size()); ++i) {
                auto& item = m_items[i];
                bool visible = ImGui::BeginTabItem(item.name.c_str(), &item.open, item.flags);
                m_tabIndices[i] = visible;

                startTabRender(visible, i);

                if(visible) {
                    if(m_lastOpenIndex != i) {
                        m_lastOpenIndex = i;
                        if(m_delegate)
                            m_delegate -> switchIndex(i);
                    }
                    if(m_renderCallback) m_renderCallback();
                    ImGui::EndTabItem();
                }

                finishTabRender(visible, i);
            }

            ImGui::EndTabBar();
        }

        postRender();
    }

}