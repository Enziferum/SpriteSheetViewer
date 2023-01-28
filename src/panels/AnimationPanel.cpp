#include <robot2D/imgui/Api.hpp>

#include <viewer/panels/AnimationPanel.hpp>
#include <viewer/Macro.hpp>
#include <viewer/Messages.hpp>
#include <viewer/FileDialog.hpp>

namespace viewer {
    namespace {
        constexpr const int min_value = 1;
        constexpr const int max_value = 100;
    }

    AnimationPanel::AnimationPanel(robot2D::MessageBus& messageBus,
                                   MessageDispatcher& messageDispatcher):
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

        robot2D::InputText("Name", &m_currentName, 0, nullptr, nullptr);
        if(m_currentAnimation >= 0 && !m_animationNames.empty() && m_currentName != m_animationNames[m_currentAnimation])
            m_animationNames[m_currentAnimation] = m_currentName;
        static auto addButtonColors = {
                robot2D::ColorButton{ robot2D::ColorButton::Type::Default, robot2D::Color::Black },
                robot2D::ColorButton{ robot2D::ColorButton::Type::Hovered, robot2D::Color::Yellow },
                robot2D::ColorButton{ robot2D::ColorButton::Type::Active, robot2D::Color::Yellow },
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
                robot2D::ColorButton{ robot2D::ColorButton::Type::Default, robot2D::Color::Black },
                robot2D::ColorButton{ robot2D::ColorButton::Type::Hovered, robot2D::Color::Green},
                robot2D::ColorButton{ robot2D::ColorButton::Type::Active, robot2D::Color::Green},
        };

        static auto deleteButtonColors = {
                robot2D::ColorButton{ robot2D::ColorButton::Type::Default, robot2D::Color::Black },
                robot2D::ColorButton{ robot2D::ColorButton::Type::Hovered, robot2D::Color::Red},
                robot2D::ColorButton{ robot2D::ColorButton::Type::Active, robot2D::Color::Red },
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
            robot2D::InputText("Name", &m_addName, 0, nullptr, nullptr);
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