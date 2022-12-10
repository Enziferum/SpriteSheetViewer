#pragma once

#include <string>
#include <robot2D/Core/Message.hpp>



namespace viewer {
    enum MessageID {
        AddAnimation = robot2D::Message::Count,
        SwitchAnimation,
        DeleteAnimation
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
}