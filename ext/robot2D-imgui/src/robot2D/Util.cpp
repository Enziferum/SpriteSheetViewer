#include <cstring>
#include <robot2D/Extra/Util.hpp>


namespace ImGui {
    ImTextureID convertTextureHandle(const unsigned int& handle) {
        ImTextureID textureID = (ImTextureID) nullptr;
        std::memcpy(&textureID, &handle, sizeof(unsigned int));
        return textureID;
    }
}