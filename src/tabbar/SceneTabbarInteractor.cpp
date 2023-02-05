#include <viewer/tabbar/SceneTabbarInteractor.hpp>
#include <viewer/tabbar/SceneTabbarController.hpp>

#include "viewer/Messages.hpp"
#include "viewer/FileDialog.hpp"

namespace viewer {
    ISceneTabbarInteractor::~ISceneTabbarInteractor() {}

    SceneTabbarInteractor::SceneTabbarInteractor(robot2D::MessageBus& messageBus,
                                                 std::vector<IDocument::Ptr>& documents,
                                                 ISceneTabbarController* controller):
                                                 m_messageBus{messageBus},
                                                 m_documents{documents},
                                                 m_controller{controller}{}

    void SceneTabbarInteractor::closeDocument(std::size_t index) {
        if(m_documents[index] -> dirty()) {
            m_documents[index] -> setClose(true);
        }
    }

    void SceneTabbarInteractor::process() {
        if (m_closeQueue.empty())
        {
            // Close queue is locked once we started a popup
            for (int doc_n = 0; doc_n < m_documents.size(); doc_n++)
            {
                auto doc = m_documents[doc_n];
                if (doc -> wantClose())
                {
                    doc -> setClose(false);
                    m_closeQueue.push_back(doc);
                }
            }
        }

        // Display closing confirmation UI
        if (!m_closeQueue.empty())
        {
            int close_queue_unsaved_documents = 0;
            for (int n = 0; n < m_closeQueue.size(); n++)
                if (m_closeQueue[n] -> dirty())
                    close_queue_unsaved_documents++;

            if (close_queue_unsaved_documents == 0)
            {
                // Close documents when all are unsaved
                for (int n = 0; n < m_closeQueue.size(); n++)
                    m_closeQueue[n] -> forceClose();
                m_closeQueue.clear();
            }
            else
            {
                if(m_controller) {
                    m_controller -> showPopup();
                }
            }
        }
    }

    void SceneTabbarInteractor::buttonYesCallback() {
        for (int n = 0; n < m_closeQueue.size(); n++)
        {
            if (m_closeQueue[n] -> dirty()) {
                //TODO(a.raag) move filedialog to router
                std::string&& filePath = viewer::saveFileDialog("SaveAnimation", ".xml", "");
                if(filePath.empty())
                    return;
                auto* msg = m_messageBus.postMessage<CloseTabMessage>(MessageID::CloseTab);
                msg -> save = true;
                msg -> savePath = std::move(filePath);
                m_controller -> closeTab(m_currentTabIndex);
            }
            m_closeQueue[n] -> forceClose();
        }
        m_closeQueue.clear();
    }

    void SceneTabbarInteractor::buttonNoCallback() {
        for (int n = 0; n < m_closeQueue.size(); n++) {
            auto* msg = m_messageBus.postMessage<CloseTabMessage>(MessageID::CloseTab);
            msg -> save = false;
            m_controller -> closeTab(m_currentTabIndex);
        }
        m_closeQueue.clear();
    }

    void SceneTabbarInteractor::buttonCancelCallback() {
        m_closeQueue.clear();
    }

    void SceneTabbarInteractor::switchIndex(std::size_t index) {
        m_currentTabIndex = index;
        auto* msg = m_messageBus.postMessage<SwitchTabMessage>(MessageID::SwitchTab);
        msg -> switchToIndex = index;
    }

}