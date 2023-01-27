#pragma once

#include <string>
#include <robot2D/Core/Message.hpp>



namespace viewer {
    enum MessageID {
        NewTab = robot2D::Message::Count,
        SwitchTab,
        CloseTab,
        AddAnimation,
        SwitchAnimation,
        DeleteAnimation,
        SaveAnimations,
        SceneViewportSize,
        LoadImage,
        LoadXml,
        AnimationPanelLoad,
        AnimationPanelAddAnimation
    };

    struct AddAnimationMessage {
        std::string name;
    };

    struct SwitchAnimationMessage {
        int indexTo;
    };

    struct DeleteAnimationMessage {
        int deleteIndex;
        int switchToIndex;
    };

    struct SaveAnimationsMessage {
        std::string filePath;
    };

    struct LoadImageMessage {
        std::string filePath;
    };

    struct LoadXmlMessage {
        std::string filePath;
    };

    struct SceneViewportMessage {
        robot2D::vec2f newSize;
    };

    struct AnimationPanelLoadMessage {
        std::string name;
    };

    struct AnimationPanelLoadEmptyMessage {
        bool needAddAnimation{false};
    };

    struct NewTabMessage {
    };

    struct SwitchTabMessage {
        int switchToIndex;
    };

    struct CloseTabMessage {
        int index;
    };
}