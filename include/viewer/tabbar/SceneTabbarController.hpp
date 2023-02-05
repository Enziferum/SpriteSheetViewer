#pragma once

#include <robot2D/imgui/Widgets.hpp>
#include "ImGui_TabbarController.hpp"
#include "SceneTabbarInteractor.hpp"

namespace viewer {

    class TabClosePopup: public robot2D::ImGui_ModalPopup {
    public:
        TabClosePopup(std::string name): robot2D::ImGui_ModalPopup(name) {}
        ~TabClosePopup() override = default;
    protected:
        void render() override;
    };

    class ISceneTabbarController {
    public:
        virtual ~ISceneTabbarController() = 0;
        virtual void showPopup() = 0;
        virtual void closeTab(int index) = 0;
    };

    class SceneTabbarController: public robot2D::ImGui_TabBarController,
                                public ISceneTabbarController,
                                 public robot2D::ImGui_TabBarControllerDelegate {
    public:
        SceneTabbarController(std::string internalName);
        ~SceneTabbarController() override = default;

        void setInteractor(ISceneTabbarInteractor::Ptr interactor);
        void setupController() override;
        void startTabRender(bool visible, int tabIndex) override;
        void finishTabRender(bool visible, int tabIndex) override;
        void postRender() override;
        void showPopup() override;
        void closeTab(int index) override;
    protected:
        void switchIndex(std::size_t index) override;
    private:
        ISceneTabbarInteractor::Ptr m_interactor{nullptr};
        TabClosePopup m_closePopup;
    };


} // namespace viewer