#include <viewer/tabbar/SceneTabbarController.hpp>

namespace viewer {

    void TabClosePopup::render() {
        ImGui::Text("Save change to the following items?");
        float item_height = ImGui::GetTextLineHeightWithSpacing();
        if (ImGui::BeginChildFrame(ImGui::GetID("frame"), ImVec2(-FLT_MIN, 6.25f * item_height)))
        {
            ImGui::EndChildFrame();
        }

        ImVec2 button_size(ImGui::GetFontSize() * 7.0f, 0.0f);
        if (ImGui::Button("Yes", button_size))
        {
            if(m_actionCallbacks[Action::Yes])
                m_actionCallbacks[Action::Yes]();
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No", button_size))
        {
            if(m_actionCallbacks[Action::No])
                m_actionCallbacks[Action::No]();
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", button_size))
        {
            if(m_actionCallbacks[Action::Cancel])
                m_actionCallbacks[Action::Cancel]();
            ImGui::CloseCurrentPopup();
        }
    }

    ISceneTabbarController::~ISceneTabbarController() {}

    SceneTabbarController::SceneTabbarController(std::string internalName):
        robot2D::ImGui_TabBarController(internalName),
        m_interactor{nullptr},
        m_closePopup{"Save"}{}

    void SceneTabbarController::setupController() {
        m_reordable = false;
        m_flags = ImGuiTabBarFlags_FittingPolicyDefault_ | (m_reordable ? ImGuiTabBarFlags_Reorderable : 0);

        m_closePopup.addCallback(robot2D::ImGui_ModalPopup::Action::Yes, [this]() {
            m_interactor -> buttonYesCallback();
        });

        m_closePopup.addCallback(robot2D::ImGui_ModalPopup::Action::No, [this]() {
            m_interactor -> buttonNoCallback();
        });

        m_closePopup.addCallback(robot2D::ImGui_ModalPopup::Action::Cancel, [this]() {
            m_interactor -> buttonCancelCallback();
        });
    }

    void SceneTabbarController::startTabRender(bool visible, int tabIndex) {
        if(!m_items[tabIndex].open) {
            m_interactor -> closeDocument(tabIndex);
            m_items[tabIndex].open = true;
        }
    }

    void SceneTabbarController::finishTabRender(bool visible, int tabIndex) {}

    void SceneTabbarController::setInteractor(ISceneTabbarInteractor::Ptr interactor) {
        m_interactor = std::move(interactor);
    }

    void SceneTabbarController::showPopup() {
        m_closePopup.selfRender();
    }

    void SceneTabbarController::switchIndex(std::size_t index) {
        m_interactor -> switchIndex(index);
    }

    void SceneTabbarController::postRender() {
        m_interactor -> process();
    }

    void SceneTabbarController::closeTab(int index) {
        m_items.erase(m_items.begin() + index);
    }

}