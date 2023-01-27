#include <robot2D/imgui/Api.hpp>
#include <imgui/imgui_internal.h>

#include <viewer/panels/ScenePanel.hpp>
#include <viewer/Macro.hpp>
#include <viewer/Messages.hpp>

namespace viewer {
    ScenePanel::ScenePanel(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher,Camera2D& camera2D):
        IPanel(typeid(ScenePanel)),
        m_messageBus{messageBus},
        m_messageDispatcher{messageDispatcher},
        m_camera2D{camera2D} {

        m_messageDispatcher.onMessage<NewTabMessage>(MessageID::NewTab,
                                                         [this](const NewTabMessage& message) {
           onNewTab();
        });

        m_messageBus.postMessage<NewTabMessage>(MessageID::NewTab);
    }

    void ScenePanel::update(float dt) {
        (void)dt;
        guiRender();
    }

    void ScenePanel::guiRender() {
        robot2D::WindowOptions windowOptions = robot2D::WindowOptions {
                {
                        {ImGuiStyleVar_WindowPadding, {0, 0}}
                },
                {}
        };
        windowOptions.flagsMask = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
        windowOptions.name = "Viewport";
        robot2D::createWindow(windowOptions, BIND_CLASS_FN(windowFunction));
    }

    bool ScenePanel::isMouseOver() const {
        return m_mouseIsOver;
    }

    void ScenePanel::windowFunction() {
        static bool opt_reorderable = false;
        static ImGuiTabBarFlags opt_fitting_flags = ImGuiTabBarFlags_FittingPolicyDefault_;

        auto* currentDockNode = ImGui::GetWindowDockNode();
        currentDockNode -> LocalFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoTabBar
                | ImGuiDockNodeFlags_NoDockingSplitMe | ImGuiDockNodeFlags_NoDockingSplitOther
                | ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingOverOther;
        currentDockNode -> UpdateMergedFlags();

        ImGuiTabBarFlags tab_bar_flags = (opt_fitting_flags) | (opt_reorderable ? ImGuiTabBarFlags_Reorderable : 0);
        bool open = true;

        if (ImGui::BeginTabBar("##tabs", tab_bar_flags))
        {
            for (int i = 0; i < m_tabNames.size(); ++i)
            {
                ImGuiTabItemFlags tab_flags = (false ? ImGuiTabItemFlags_UnsavedDocument : 0);
                bool visible = ImGui::BeginTabItem(m_tabNames[i].c_str(), &open, tab_flags);
                m_tabIndices[i] = visible;

                if (visible)
                {
                    if(m_lastOpenIndex != i) {
                        auto* msg = m_messageBus.postMessage<SwitchTabMessage>(MessageID::SwitchTab);
                        msg -> switchToIndex = i;
                        m_lastOpenIndex = i;
                    }
                    showScene();
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    }

    void ScenePanel::showScene() {
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        //auto viewportMinRegion = ImGui::GetContentRegionAvail();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x,
                                viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x,
                                viewportMaxRegion.y + viewportOffset.y };

        auto ViewPanelSize = ImGui::GetContentRegionAvail();
        robot2D::vec2u viewSize = {static_cast<unsigned>(ViewPanelSize.x),
                                   static_cast<unsigned>(ViewPanelSize.y)};
        if(m_ViewportSize != viewSize) {
            m_ViewportSize = viewSize;
            m_framebuffer -> Resize(m_ViewportSize);
            m_camera2D.resetViewport(m_ViewportSize.as<float>());

            auto* msg = m_messageBus.postMessage<SceneViewportMessage>(MessageID::SceneViewportSize);
            msg -> newSize = viewSize.as<float>();
        }

        robot2D::RenderFrameBuffer(m_framebuffer, m_ViewportSize.as<float>());
    }

    void ScenePanel::onNewTab() {
        std::string newTabName = "Tab " + std::to_string(m_tabNames.size() + 1);
        m_tabNames.emplace_back(std::move(newTabName));
        m_tabIndices[m_tabNames.size() - 1] = true;
        m_lastOpenIndex = m_tabNames.size() - 1;
    }

} // namespace viewer