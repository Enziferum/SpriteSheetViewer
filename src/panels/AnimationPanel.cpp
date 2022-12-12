#include <robot2D/imgui/Api.hpp>

#include <viewer/panels/AnimationPanel.hpp>
#include <viewer/macro.hpp>
#include <viewer/Messages.hpp>

namespace viewer {
    namespace {
        constexpr float min_value = 1.f;
        constexpr float max_value = 100.f;
    }

    using closeCallback = void(*)();
    template<typename ImGuiFunc, typename ... Args>
    void imguiFunc(ImGuiFunc&& func, closeCallback&& close, Args&& ... args) {
        if(func(std::forward<Args>(args)...)) {
            close();
        }
    }

    class Button {
    public:
        Button();
        Button(std::string title);
        Button(std::string title, std::initializer_list<robot2D::Color> colors);
        ~Button();

        template<
                typename Func,
                typename ...Args,
                typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>
        >
        void onCall(Func&& func, Args&& ... args) {
            if(ImGui::Begin(m_title.c_str()))
                func(std::forward<Args>(args)...);
        }
    private:
        void pushColors(const std::initializer_list<robot2D::Color>& colors);
    private:
        std::string m_title;
        std::array<robot2D::Color, 3> m_buttonColors;
    };

    Button::Button(): m_title{"Default"}, m_buttonColors{} {

    }

    Button::Button(std::string title): m_title{title}, m_buttonColors{} {

    }

    Button::Button(std::string title, std::initializer_list<robot2D::Color> colors):
            m_title{title} {
        pushColors(colors);
    }

    void Button::pushColors(const std::initializer_list<robot2D::Color>& colors) {
        int index = 0;
        for(const auto& color: colors) {
            m_buttonColors[index] = color;
            ++index;
        }
    }

    Button::~Button() {
        if(!m_buttonColors.empty())
            ImGui::PopStyleColor(m_buttonColors.size());
        ImGui::PopID();
    }

    struct ColorButton {
        enum class Type {
            Default, Hovered, Active
        };

        robot2D::Color color;
    };

    template<
            typename Func,
            typename ...Args,
            typename = std::enable_if_t<std::is_invocable_v<Func, Args...>>
    >
    void colorButton(std::string title, Func&& func, Args&& ... args) {
        if(ImGui::Button(title.c_str()))
            func(std::forward<Args>(args)...);
    }

    struct InputTextCallback_UserData
    {
        std::string*            Str;
        ImGuiInputTextCallback  ChainCallback;
        void*                   ChainCallbackUserData;
    };

    static int InputTextCallback(ImGuiInputTextCallbackData* data)
    {
        InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
        {
            // Resize string callback
            // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
            std::string* str = user_data->Str;
            IM_ASSERT(data->Buf == str->c_str());
            str->resize(data->BufTextLen);
            data->Buf = (char*)str->c_str();
        }
        else if (user_data->ChainCallback)
        {
            // Forward to user callback, if any
            data->UserData = user_data->ChainCallbackUserData;
            return user_data->ChainCallback(data);
        }
        return 0;
    }

    bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags,
                   ImGuiInputTextCallback callback, void* user_data)
    {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        flags |= ImGuiInputTextFlags_CallbackResize;

        InputTextCallback_UserData cb_user_data;
        cb_user_data.Str = str;
        cb_user_data.ChainCallback = callback;
        cb_user_data.ChainCallbackUserData = user_data;
        return ImGui::InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
    }

    AnimationPanel::AnimationPanel(robot2D::MessageBus& messageBus):
        IPanel(typeid(AnimationPanel)),
        m_messageBus{messageBus} {
        m_currentName = "New Animation";
        onAdd();
    }

    void AnimationPanel::update(float dt) {
        robot2D::WindowOptions windowOptions = robot2D::WindowOptions {
                {
                        {ImGuiStyleVar_WindowPadding, {0, 0}}
                },
                {}
        };
        // ImGuiWindowFlags_NoTitleBar
        windowOptions.flagsMask =  ImGuiWindowFlags_NoScrollbar;
        windowOptions.name = "AnimationPanel";

        robot2D::createWindow(windowOptions, [this]() { windowFunction(); });
    }


    void AnimationPanel::windowFunction() {

        checkMouseHover();

        InputText("Name", &m_currentName, 0, nullptr, nullptr);
        colorButton("Add", BIND_CLASS_FN(onAdd));

        ImGui::LabelText("Frame count ", "%i", m_animation ? m_animation -> getFramesCount() : 0);
        if(m_animation)
            if (!ImGui::SliderFloat("Speed", &m_animation -> getSpeed(), min_value, max_value)) {}

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

        colorButton("Save", BIND_CLASS_FN(onSave));
        ImGui::SameLine();
        colorButton("Delete", BIND_CLASS_FN(onDelete));
    }

    void AnimationPanel::setAnimation(SpriteSheetAnimation* animation) {
        m_animation = animation;
    }

    void AnimationPanel::onAdd() {
        auto* msg = m_messageBus.postMessage<AddAnimationMessage>(MessageID::AddAnimation);
        msg -> name = m_currentName;
        m_animationNames.emplace_back(m_currentName);
        m_currentAnimation = m_animationNames.size() - 1;
        m_lastCurrentAnimation = m_currentAnimation;
        m_currentName = m_animationNames[m_currentAnimation];
    }

    void AnimationPanel::onSave() {

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


} // namespace viewer