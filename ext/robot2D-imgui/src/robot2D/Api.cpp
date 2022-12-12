#include <imgui/imgui.h>

#include <robot2D/imgui/Api.hpp>
#include <robot2D/imgui/Util.hpp>

namespace robot2D {

    template<typename F,
            typename = std::enable_if_t<std::is_invocable_v<F>>>
    struct Defer {
        Defer(F&& func):
                m_func{std::move(func)}{}

        ~Defer() {
            try{
                if(m_func)
                    m_func();
            }
            catch (...) {}
        }

        F m_func;
    };

    void createWindow(const WindowOptions& windowOptions, std::function<void()>&& callback) {
        windowOptions.enable();
        ImGui::Begin(windowOptions.name.c_str(),
              nullptr,
              windowOptions.flagsMask);
        Defer defer{&ImGui::End};
        callback();
        // TODO(a.raag): windowOptions inside Defer
        windowOptions.disable();
    }

    void Image(robot2D::Sprite& sprite, const robot2D::vec2f& size) {
        const robot2D::Texture* sprTexture = sprite.getTexture();
        if(!sprTexture || size == robot2D::vec2f{})
            return;
        const robot2D::Texture& texture = *sprTexture;
        robot2D::vec2f textureSize = {texture.getSize().x, texture.getSize().y};
        auto textureRect = sprite.getLocalBounds();

        auto imID = ImGui::convertTextureHandle(texture.getID());
        ImVec2 uv0(textureRect.lx / textureSize.x, textureRect.ly / textureSize.y);
        ImVec2 uv1((textureRect.lx + textureRect.width) / textureSize.x,
                   (textureRect.ly + textureRect.height) / textureSize.y);
        ImGui::Image(imID, ImVec2(size.x, size.y), uv0, uv1);
    }

    void AnimatedImage(robot2D::Sprite& sprite, const robot2D::vec2f& size) {
        const robot2D::Texture* sprTexture = sprite.getTexture();
        if(!sprTexture || size == robot2D::vec2f{})
            return;
        const robot2D::Texture& texture = *sprTexture;
        robot2D::vec2f textureSize = {texture.getSize().x, texture.getSize().y};
        auto textureRect = sprite.getTextureRect();

        auto imID = ImGui::convertTextureHandle(texture.getID());
        ImVec2 uv0(textureRect.lx / textureSize.x, textureRect.ly / textureSize.y);
        ImVec2 uv1((textureRect.lx + textureRect.width) / textureSize.x,
                   (textureRect.ly + textureRect.height) / textureSize.y);
        ImGui::Image(imID, ImVec2(size.x, size.y), uv0, uv1);
    }

    void RenderFrameBuffer(const robot2D::FrameBuffer::Ptr& frameBuffer, const robot2D::vec2f& size) {
        auto imID = ImGui::convertTextureHandle(frameBuffer -> getFrameBufferRenderID());
        ImGui::Image(imID, ImVec2(size.x, size.y), {0,1}, {1, 0});
    }

    bool ImageButton(const robot2D::Texture& texture, const robot2D::vec2f& size) {
        auto imID = ImGui::convertTextureHandle(texture.getID());
        return ImGui::ImageButton(imID, ImVec2(size.x, size.y), {0, 0},
                                  {1,1}, 0);
    }

    void dummyDragDrop(const std::string& payloadName, std::function<void(std::string)>&& callback) {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadName.c_str())) {
                const char* data = reinterpret_cast<const char*>(payload -> Data);
                if(data) {
                    std::string payloadString = std::string(data, payload->DataSize);
                    callback(payloadString);
                }
            }
            ImGui::EndDragDropTarget();
        }
    }
} // namespace robot2D