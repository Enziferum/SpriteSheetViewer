#include <robot2D/imgui/Api.hpp>

#include <viewer/panels/AnimationPanel.hpp>
#include <viewer/macro.hpp>
#include <viewer/Messages.hpp>
#include <viewer/FileDialog.hpp>

namespace viewer {
    namespace {
        constexpr const int min_value = 1;
        constexpr const int max_value = 100;
    }

    /////////////////////////////////// Move to ROBOT2D_IMGUI /////////////////////////////////////////////
    struct ColorButton {
        enum class Type {
            Default, Hovered, Active
        } type;

        robot2D::Color color;
    };

    template<
            typename Func,
            typename ...Args,
            typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>
    >
    void colorButton(std::string title,
                     std::initializer_list<ColorButton> colors,
                     Func&& func, Args&& ... args) {
        ImGui::PushID(title.c_str());
        for(const auto& color: colors) {
            switch(color.type) {
                case ColorButton::Type::Default:
                    ImGui::PushStyleColor(
                            ImGuiCol_Button,
                            (ImVec4)ImColor{
                                color.color.red,
                                color.color.green,
                                color.color.blue,
                                color.color.alpha
                            }
                    );
                    break;
                case ColorButton::Type::Hovered:
                    ImGui::PushStyleColor(
                            ImGuiCol_ButtonHovered,
                            (ImVec4)ImColor{
                                    color.color.red,
                                    color.color.green,
                                    color.color.blue,
                                    color.color.alpha
                            }
                    );
                    break;
                case ColorButton::Type::Active:
                    ImGui::PushStyleColor(
                            ImGuiCol_ButtonActive,
                            (ImVec4)ImColor{
                                    color.color.red,
                                    color.color.green,
                                    color.color.blue,
                                    color.color.alpha
                            }
                    );
                    break;
            }
        }
        if(ImGui::Button(title.c_str()))
            func(std::forward<Args>(args)...);
        ImGui::PopStyleColor(static_cast<int>(colors.size()));
        ImGui::PopID();
    }


    struct InputTextCallback_UserData
    {
        std::string*            Str;
        ImGuiInputTextCallback  ChainCallback;
        void*                   ChainCallbackUserData;
    };

    static int InputTextCallback(ImGuiInputTextCallbackData* data)
    {
        auto* user_data = static_cast<InputTextCallback_UserData*>(data -> UserData);
        assert(user_data != nullptr && "InputTextCallback user data can't be nullptr");
        if (data -> EventFlag == ImGuiInputTextFlags_CallbackResize)
        {
            // Resize string callback
            // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
            std::string* str = user_data -> Str;
            IM_ASSERT(data -> Buf == str -> c_str());
            str -> resize(data -> BufTextLen);
            data -> Buf = const_cast<char*>(str -> c_str());
        }
        else if (user_data->ChainCallback)
        {
            // Forward to user callback, if any
            data -> UserData = user_data -> ChainCallbackUserData;
            return user_data->ChainCallback(data);
        }
        return 0;
    }

    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags,
                   ImGuiInputTextCallback callback, void* user_data)
    {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        InputTextCallback_UserData cb_user_data{};
        cb_user_data.Str = str;
        cb_user_data.ChainCallback = callback;
        cb_user_data.ChainCallbackUserData = user_data;
        return ImGui::InputText(
                label,
                const_cast<char*>(str->c_str()),
                str -> capacity() + 1,
                flags,
                InputTextCallback,
                &cb_user_data
        );
    }

    /////////////////////////////////// Move to ROBOT2D_IMGUI /////////////////////////////////////////////


    AnimationPanel::AnimationPanel(robot2D::MessageBus& messageBus, MessageDispatcher& messageDispatcher):
        IPanel(typeid(AnimationPanel)),
        m_messageBus{messageBus},
        m_messageDispatcher{messageDispatcher} {
        m_currentName = "Default Animation";
        m_addName = "Default Animation";

        setup();
    }

    void AnimationPanel::setup() {
        onAdd();

        m_messageDispatcher.onMessage<AnimationPanelLoadEmptyMessage>(
                MessageID::AnimationPanelLoad, BIND_CLASS_FN(onLoad));

        m_messageDispatcher.onMessage<AnimationPanelLoadMessage>(
                MessageID::AnimationPanelAddAnimation, BIND_CLASS_FN(onLoadAnimation));
    }


    void AnimationPanel::update(float dt) {
        (void)dt;
        auto windowOptions = robot2D::WindowOptions {
                {
                        { ImGuiStyleVar_WindowPadding, {0, 0} }
                },
                {}
        };
        // ImGuiWindowFlags_NoTitleBar
        windowOptions.flagsMask =  ImGuiWindowFlags_NoScrollbar;
        windowOptions.name = "AnimationPanel";

        robot2D::createWindow(windowOptions, BIND_CLASS_FN(windowFunction));
    }


    void AnimationPanel::windowFunction() {
        checkMouseHover();

        InputText("Name", &m_currentName, 0, nullptr, nullptr);
        if(m_currentAnimation >= 0 && !m_animationNames.empty() && m_currentName != m_animationNames[m_currentAnimation])
            m_animationNames[m_currentAnimation] = m_currentName;
        static auto addButtonColors = {
                ColorButton{ ColorButton::Type::Default, robot2D::Color::Black },
                ColorButton{ ColorButton::Type::Hovered, robot2D::Color::Yellow },
                ColorButton{ ColorButton::Type::Active, robot2D::Color::Yellow },
        };

        colorButton("Add", addButtonColors, [this]() { m_needShowModal = true; });

        if(m_needShowModal)
           showAddAnimationPanel();

        ImGui::LabelText("Frame count ", "%lli", m_animation ? m_animation -> getFramesCount() : 0);
        if(m_animation && m_animation -> getSpeed())
            if (!ImGui::SliderInt("Speed", m_animation -> getSpeed(), min_value, max_value)) {}

        float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        ImGui::PushButtonRepeat(true);
        if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
            if(m_animation)
                m_animation -> decreaseVisibleFrames();
        }
        ImGui::SameLine(0.0f, spacing);
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
            if(m_animation)
                m_animation -> increaseVisibleFrames();
        }
        ImGui::PopButtonRepeat();
        ImGui::SameLine();
        ImGui::Text("%d", m_animation ? m_animation -> getVisibleFrameCounts() : 0);

        std::string previewValue = m_lastCurrentAnimation >= 0
                    ? m_animationNames[m_lastCurrentAnimation] : "Default";

        if (ImGui::BeginCombo("Animations", previewValue.c_str(), 0))
        {
            for (int n = 0; n < m_animationNames.size(); ++n)
            {
                const bool is_selected = (m_currentAnimation == n);
                if (ImGui::Selectable(m_animationNames[n].c_str(), is_selected)) {
                    m_currentAnimation = n;
                    auto* msg = m_messageBus.postMessage<SwitchAnimationMessage>(MessageID::SwitchAnimation);
                    msg -> indexTo = m_currentAnimation;
                    m_currentName = m_animationNames[m_currentAnimation];
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if(m_currentAnimation != m_lastCurrentAnimation) {
            m_lastCurrentAnimation = m_currentAnimation;
        }

        static auto saveButtonColors = {
                ColorButton{ ColorButton::Type::Default, robot2D::Color::Black },
                ColorButton{ ColorButton::Type::Hovered, robot2D::Color::Green},
                ColorButton{ ColorButton::Type::Active, robot2D::Color::Green},
        };

        static auto deleteButtonColors = {
                ColorButton{ ColorButton::Type::Default, robot2D::Color::Black },
                ColorButton{ ColorButton::Type::Hovered, robot2D::Color::Red},
                ColorButton{ ColorButton::Type::Active, robot2D::Color::Red },
        };

        colorButton("Save", saveButtonColors, BIND_CLASS_FN(onSave));
        ImGui::SameLine();
        colorButton("Delete", deleteButtonColors, BIND_CLASS_FN(onDelete));
    }

    void AnimationPanel::setAnimation(SpriteSheetAnimation* animation) {
        m_animation = animation;
    }

    void AnimationPanel::onAdd() {
        auto* msg = m_messageBus.postMessage<AddAnimationMessage>(MessageID::AddAnimation);
        msg -> name = m_addName;
        m_animationNames.emplace_back(m_addName);
        m_currentAnimation = m_animationNames.size() - 1;
        m_lastCurrentAnimation = m_currentAnimation;
        m_currentName = m_animationNames[m_currentAnimation];
    }

    void AnimationPanel::onSave() {
        std::string&& filePath = viewer::saveFileDialog("SaveAnimation", ".xml", "");
        if(filePath.empty())
            return;
        auto* msg = m_messageBus.postMessage<SaveAnimationsMessage>(MessageID::SaveAnimations);
        msg -> filePath = std::move(filePath);
    }

    void AnimationPanel::onDelete() {
        m_animationNames.erase(m_animationNames.begin() + m_currentAnimation);
        auto* msg = m_messageBus.postMessage<DeleteAnimationMessage>(MessageID::DeleteAnimation);
        msg -> deleteIndex = m_currentAnimation;

        int switchIndex = m_currentAnimation;
        if(m_currentAnimation >= 1) {
            --m_currentAnimation;
            --m_lastCurrentAnimation;
            --switchIndex;
        }
        m_currentName = m_animationNames[switchIndex];
        msg -> switchToIndex = switchIndex;
    }

    void AnimationPanel::onLoad(const AnimationPanelLoadEmptyMessage& message) {
        m_animationNames.clear();
        m_currentName = "Default Animation";
        m_addName = "Default Animation";
        m_currentAnimation = 0;
        m_lastCurrentAnimation = -1;
        if(message.needAddAnimation)
            onAdd();
    }

    void AnimationPanel::onLoadAnimation(const AnimationPanelLoadMessage& message) {
        if(m_animationNames.empty())
            m_currentName = message.name;
        m_animationNames.emplace_back(message.name);
    }

    void AnimationPanel::showAddAnimationPanel() {
        ImGui::OpenPopup("Add Animation");
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        if(ImGui::BeginPopupModal("Add Animation", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            setMouseHoverDirectly(true);
            ImGui::Text("Enter animation's name");
            ImGui::Separator();
            InputText("Name", &m_addName, 0, nullptr, nullptr);
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                setMouseHoverDirectly(false);
                m_needShowModal = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("OK", ImVec2(120, 0))) {
                setMouseHoverDirectly(false);
                m_needShowModal = false;
                onAdd();
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

} // namespace viewer