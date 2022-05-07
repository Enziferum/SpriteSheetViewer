#include <imgui/imgui.h>
#include <robot2D/Extra/Api.hpp>
#include <robot2D/Extra/Util.hpp>

namespace ImGui {

    void createWindow(const WindowOptions& windowOptions, std::function<void()>&& callback) {
        windowOptions.enable();
        Begin(windowOptions.name.c_str(),
              nullptr,
              windowOptions.flagsMask);

        callback();

        windowOptions.disable();
        End();
    }

    void Image(robot2D::Sprite& sprite, const robot2D::vec2f& size) {
        const robot2D::Texture* sprTexture = sprite.getTexture();
        if(!sprTexture || size == robot2D::vec2f{})
            return;
        const robot2D::Texture& texture = *sprTexture;
        robot2D::vec2f textureSize = {texture.getSize().x, texture.getSize().y};
        auto textureRect = sprite.getLocalBounds();

        auto imID = convertTextureHandle(texture.getID());
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

        auto imID = convertTextureHandle(texture.getID());
        ImVec2 uv0(textureRect.lx / textureSize.x, textureRect.ly / textureSize.y);
        ImVec2 uv1((textureRect.lx + textureRect.width) / textureSize.x,
                   (textureRect.ly + textureRect.height) / textureSize.y);
        ImGui::Image(imID, ImVec2(size.x, size.y), uv0, uv1);
    }

    void RenderFrameBuffer(const robot2D::FrameBuffer::Ptr& frameBuffer, const robot2D::vec2f& size) {
        auto imID = convertTextureHandle(frameBuffer -> getFrameBufferRenderID());
        ImGui::Image(imID, ImVec2(size.x, size.y), {0,1}, {1, 0});
    }

    bool ImageButton(const robot2D::Texture& texture, const robot2D::vec2f& size) {
        auto imID = convertTextureHandle(texture.getID());
        return ImGui::ImageButton(imID, ImVec2(size.x, size.y), {0, 0},
                                  {1,1}, 0);
    }

    void dummyDragDrop(const std::string& payloadName, std::function<void(std::string)> &&callback) {
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadName.c_str())) {
                std::string payloadString = std::string((const char*)payload->Data, payload->DataSize);
                callback(payloadString);
            }
            ImGui::EndDragDropTarget();
        }
    }
}