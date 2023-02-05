#include <robot2D/imgui/Api.hpp>
#include <robot2D/imgui/Widgets.hpp>
#include <imgui/imgui_internal.h>

#include <viewer/panels/ScenePanel.hpp>
#include <viewer/Macro.hpp>
#include <viewer/Messages.hpp>
#include <viewer/FileDialog.hpp>

namespace viewer {
    ScenePanel::ScenePanel(
            robot2D::MessageBus& messageBus,
            MessageDispatcher& messageDispatcher,
            Camera2D& camera2D,
            std::vector<IDocument::Ptr>& documents
    ):
        IPanel(typeid(ScenePanel)),
        m_messageBus{messageBus},
        m_messageDispatcher{messageDispatcher},
        m_camera2D{camera2D},
        m_tabbarController{"##tabs"}
    {

            m_messageDispatcher.onMessage<NewTabMessage>(MessageID::NewTab, BIND_CLASS_FN(onNewTab));

            m_tabbarInteractor = std::make_unique<SceneTabbarInteractor>(m_messageBus, documents, &m_tabbarController);
            m_tabbarController.setupController();
            m_tabbarController.setInteractor(std::move(m_tabbarInteractor));
            m_tabbarController.setVisibleRenderCallback([this]() { showScene(); });
            m_tabbarController.setDelegate(&m_tabbarController);

            robot2D::TabBarItem tabBarItem{};
            tabBarItem.name = "Tab 1";
            m_tabbarController.addTab(tabBarItem);
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
        auto* currentDockNode = ImGui::GetWindowDockNode();
        currentDockNode -> LocalFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoTabBar
                | ImGuiDockNodeFlags_NoDockingSplitMe | ImGuiDockNodeFlags_NoDockingSplitOther
                | ImGuiDockNodeFlags_NoDockingOverMe | ImGuiDockNodeFlags_NoDockingOverOther;
        currentDockNode -> UpdateMergedFlags();

        m_tabbarController.render();
    }

    void ScenePanel::showScene() {
        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x,
                                viewportMinRegion.y + viewportOffset.y};
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x,
                                viewportMaxRegion.y + viewportOffset.y };

        auto ViewPanelSize = ImGui::GetContentRegionAvail();
        robot2D::vec2u viewSize = {static_cast<unsigned>(ViewPanelSize.x),
                                   static_cast<unsigned>(ViewPanelSize.y)};

        m_ViewportBounds[0] = {viewportOffset.x, viewportOffset.y + (viewportMaxRegion.y - ViewPanelSize.y)};

        if(m_ViewportSize != viewSize) {
            m_ViewportSize = viewSize;
            m_framebuffer -> Resize(m_ViewportSize);
            m_camera2D.resetViewport(m_ViewportSize.as<float>());

            auto* msg = m_messageBus.postMessage<SceneViewportMessage>(MessageID::SceneViewportSize);
            msg -> newSize = viewSize.as<float>();
        }

        robot2D::RenderFrameBuffer(m_framebuffer, m_ViewportSize.as<float>());
    }

    void ScenePanel::onNewTab(const NewTabMessage& message) {
        static int cnt = 1;
        std::string newTabName = "Tab " + std::to_string(++cnt);

        robot2D::TabBarItem tabBarItem{};
        tabBarItem.name = newTabName;
        m_tabbarController.addTab(tabBarItem);
    }

} // namespace viewer