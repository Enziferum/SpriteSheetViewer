#pragma once

#include <memory>
#include <vector>

#include <robot2D/Core/MessageBus.hpp>
#include <viewer/IDocument.hpp>

namespace viewer {
    class ISceneTabbarInteractor {
    public:
        using Ptr = std::unique_ptr<ISceneTabbarInteractor>;
    public:
        virtual ~ISceneTabbarInteractor() = 0;
        virtual void buttonYesCallback() = 0;
        virtual void buttonNoCallback() = 0;
        virtual void buttonCancelCallback() = 0;
        virtual void closeDocument(std::size_t index) = 0;
        virtual void switchIndex(std::size_t index) = 0;
        virtual void process() = 0;
    };

    class ISceneTabbarController;
    class SceneTabbarInteractor: public ISceneTabbarInteractor {
    public:
        SceneTabbarInteractor(robot2D::MessageBus& messageBus, std::vector<IDocument::Ptr>& documents,
                              ISceneTabbarController*);
        ~SceneTabbarInteractor() override = default;

        void closeDocument(std::size_t index) override;
        void process() override;
        void switchIndex(std::size_t index) override;

        virtual void buttonYesCallback() override;
        virtual void buttonNoCallback() override;
        virtual void buttonCancelCallback() override;
    private:
        robot2D::MessageBus& m_messageBus;
        std::vector<IDocument::Ptr>& m_documents;
        std::vector<IDocument::Ptr> m_closeQueue;
        ISceneTabbarController* m_controller;
        int m_currentTabIndex = 0;
    };
} // namespace viewer