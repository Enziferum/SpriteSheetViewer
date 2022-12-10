/*********************************************************************
(c) Alex Raag 2021
https://github.com/Enziferum
robot2D - Zlib license.
This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.
2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#include <robot2D/Extra/Gui.hpp>
#include <robot2D/Extra/Util.hpp>

namespace ImGui {


    Gui::Gui():
    m_window(nullptr),
    m_windowHasFocus{true},
    m_mouseMoved{false},
    m_mousePressed{},
    m_render{}
    {
        m_mousePressed[0] = false;
        m_mousePressed[1] = false;
        m_mousePressed[2] = false;
    }

    Gui::~Gui() {
        shutdown();
    }

    void Gui::init(robot2D::Window& window) {
        m_window = &window;
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.BackendPlatformName = "ImGui_robot2D";
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        io.KeyMap[ImGuiKey_Tab] = robot2D::key2Int(robot2D::Key::TAB);
        io.KeyMap[ImGuiKey_LeftArrow] = robot2D::key2Int(robot2D::Key::LEFT);
        io.KeyMap[ImGuiKey_RightArrow] =robot2D::key2Int(robot2D::Key::RIGHT);
        io.KeyMap[ImGuiKey_UpArrow] = robot2D::key2Int(robot2D::Key::UP);
        io.KeyMap[ImGuiKey_DownArrow] = robot2D::key2Int(robot2D::Key::DOWN);
        io.KeyMap[ImGuiKey_PageUp] = robot2D::key2Int(robot2D::Key::PAGE_UP);
        io.KeyMap[ImGuiKey_PageDown] = robot2D::key2Int(robot2D::Key::PAGE_DOWN);
        io.KeyMap[ImGuiKey_Home] = robot2D::key2Int(robot2D::Key::HOME);
        io.KeyMap[ImGuiKey_End] = robot2D::key2Int(robot2D::Key::END);
        io.KeyMap[ImGuiKey_Insert] = robot2D::key2Int(robot2D::Key::INSERT);
        io.KeyMap[ImGuiKey_Delete] = robot2D::key2Int(robot2D::Key::DEL);
        io.KeyMap[ImGuiKey_Backspace] = robot2D::key2Int(robot2D::Key::BACKSPACE);
        io.KeyMap[ImGuiKey_Space] = robot2D::key2Int(robot2D::Key::SPACE);
        io.KeyMap[ImGuiKey_Enter] = robot2D::key2Int(robot2D::Key::ENTER);
        io.KeyMap[ImGuiKey_Escape] = robot2D::key2Int(robot2D::Key::ESCAPE);
        io.KeyMap[ImGuiKey_A] = robot2D::key2Int(robot2D::Key::A);
        io.KeyMap[ImGuiKey_C] = robot2D::key2Int(robot2D::Key::C);
        io.KeyMap[ImGuiKey_V] = robot2D::key2Int(robot2D::Key::V);
        io.KeyMap[ImGuiKey_X] = robot2D::key2Int(robot2D::Key::X);
        io.KeyMap[ImGuiKey_Y] = robot2D::key2Int(robot2D::Key::Y);
        io.KeyMap[ImGuiKey_Z] = robot2D::key2Int(robot2D::Key::Z);

        /*
            io.ClipboardUserData = (GLFWwindow*)m_window->getRaw();
            io.GetClipboardTextFn = Glfw_GetClipboardText;
            io.SetClipboardTextFn = Glfw_SetClipboardText;
        */

        auto sz = window.getSize();
        io.DisplaySize = ImVec2(static_cast<float>(sz.x),
                                static_cast<float>(sz.y));

        m_cursors[ImGuiMouseCursor_Arrow].createDefault();
        m_cursors[ImGuiMouseCursor_TextInput].create(robot2D::CursorType::TextInput);
        m_cursors[ImGuiMouseCursor_ResizeNS].create(robot2D::CursorType::ResizeUpDown);
        m_cursors[ImGuiMouseCursor_ResizeEW].create(robot2D::CursorType::ResizeLeftRight);
        m_cursors[ImGuiMouseCursor_Hand].create(robot2D::CursorType::Hand);
        m_cursors[ImGuiMouseCursor_ResizeAll].createDefault();
        m_cursors[ImGuiMouseCursor_ResizeNESW].createDefault();
        m_cursors[ImGuiMouseCursor_ResizeNWSE].createDefault();
        m_cursors[ImGuiMouseCursor_NotAllowed].createDefault();

        m_render.setup();
    }


    void Gui::handleEvents(const robot2D::Event &event) {
        if(m_windowHasFocus) {
            ImGuiIO& io = ImGui::GetIO();
            switch(event.type) {
                case robot2D::Event::MouseMoved:
                    m_mouseMoved = true;
                    break;
                case robot2D::Event::MousePressed:
                case robot2D::Event::MouseReleased: {
                    int button = event.mouse.btn;
                    if (event.type == robot2D::Event::MousePressed && button >= 0 && button < 3) {
                        m_mousePressed[event.mouse.btn] = true;
                    }
                } break;
                case robot2D::Event::MouseWheel:
                    io.MouseWheelH += event.wheel.scroll_x;
                    io.MouseWheel += event.wheel.scroll_y;
                    break;
                case robot2D::Event::KeyPressed:
                case robot2D::Event::KeyReleased: {
                    int key = robot2D::key2Int(event.key.code);
                    if(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown)) {
                        io.KeysDown[key] = (event.type == robot2D::Event::KeyPressed);
                    }

                    io.KeyCtrl = io.KeysDown[robot2D::key2Int(robot2D::Key::LEFT_CONTROL)]
                            || io.KeysDown[robot2D::key2Int(robot2D::Key::RIGHT_CONTROL)];
                    io.KeyShift = io.KeysDown[robot2D::key2Int(robot2D::Key::LEFT_SHIFT)]
                            || io.KeysDown[robot2D::key2Int(robot2D::Key::RIGHT_SHIFT)];
                    io.KeyAlt = io.KeysDown[robot2D::key2Int(robot2D::Key::LEFT_ALT)]
                            || io.KeysDown[robot2D::key2Int(robot2D::Key::RIGHT_ALT)];
#ifdef _WIN32
                    io.KeySuper = false;
#else
                   // io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
                } break;
                case robot2D::Event::TextEntered:
                    io.AddInputCharacter(event.text.symbol);
                    break;
                default:
                    break;
            }
        }

        switch(event.type) {
            case robot2D::Event::LostFocus: {
                ImGuiIO& io = ImGui::GetIO();
                for(int it = 0; it < IM_ARRAYSIZE(io.KeysDown); ++it)
                    io.KeysDown[it] = false;
                io.KeyCtrl = false;
                io.KeyAlt = false;
                io.KeyShift = false;
                io.KeySuper = false;
                m_windowHasFocus = false;
            } break;
            case robot2D::Event::GainFocus:
                m_windowHasFocus = true;
                break;
            default:
                break;
        }
    }

    void Gui::updateMouseCursor() {
        ImGuiIO& io = ImGui::GetIO();
        if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) == 0) {
            ImGuiMouseCursor cursor = ImGui::GetMouseCursor();
            if (io.MouseDrawCursor || cursor == ImGuiMouseCursor_None) {
                m_window -> setMouseCursorVisible(false);
            } else {
                m_window -> setMouseCursorVisible(true);
                if(cursor < ImGuiMouseCursor_COUNT)
                    m_window -> setCursor(m_cursors[cursor]);
                else
                    m_window -> setCursor(m_cursors[ImGuiMouseCursor_Arrow]);
            }
        }
    }

    void Gui::update(float dt) {
        ImGuiIO& io = ImGui::GetIO();
        updateMouseCursor();

        auto sz = m_window -> getSize();
        io.DisplaySize = ImVec2(static_cast<float>(sz.x),
                                static_cast<float>(sz.y));
        io.DeltaTime = dt;
        if(m_windowHasFocus) {
            if(io.WantSetMousePos) {
                robot2D::vec2f newMousePos = {io.MousePos.x, io.MousePos.y};
                m_window -> setMousePos(newMousePos);
            } else {
                auto mousePos = m_window -> getMousePos();
                io.MousePos = ImVec2(mousePos.x, mousePos.y);
            }
            for (unsigned int it = 0; it < 3; it++) {
                bool mousePressed = m_window -> isMousePressed(static_cast<robot2D::Mouse>(it));
                io.MouseDown[it] = m_mousePressed[it] || mousePressed;
                m_mousePressed[it] = false;
            }
        }

        if(io.MouseDrawCursor) {
            m_window->setMouseCursorVisible(false);
        }

        ImGui::NewFrame();
    }

    void Gui::render() {
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        m_render.render(draw_data);
    }

    void Gui::shutdown() {
        ImGui::GetIO().Fonts->SetTexID(convertTextureHandle(0));
        ImGui::DestroyContext();
    }

}