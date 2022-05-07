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

#pragma once

#include <functional>

#include <robot2D/Graphics/Sprite.hpp>
#include <robot2D/Graphics/FrameBuffer.hpp>

#include "WindowOptions.hpp"

namespace ImGui {
    void createWindow(const WindowOptions& windowOptions, std::function<void()>&& callback);
    void dummyDragDrop(const std::string& payloadName, std::function<void(std::string)>&& callback);
    void Image(robot2D::Sprite& sprite, const robot2D::vec2f& size);
    void AnimatedImage(robot2D::Sprite& sprite, const robot2D::vec2f& size);
    bool ImageButton(const robot2D::Texture& texture, const robot2D::vec2f& size);
    void RenderFrameBuffer(const robot2D::FrameBuffer::Ptr& frameBuffer, const robot2D::vec2f& size);
}