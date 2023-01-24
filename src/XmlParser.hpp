#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <robot2D/Core/Vector2.hpp>
#include <robot2D/Graphics/Color.hpp>
#include <viewer/Animation.hpp>

namespace viewer {
    class IParser {
    public:
        virtual ~IParser() = 0;
        virtual bool loadFromFile(const std::string& path, std::string& texturePath, AnimationList& animations) = 0;
        virtual bool saveToFile(const std::string& path,
                                const std::string& texturePath,
                                const robot2D::Color& maskColor,
                                const AnimationList& animationList,
                                robot2D::vec2f realTexturePos) = 0;
    };

    class XmlParser: public IParser {
    public:
        XmlParser();
        ~XmlParser() override = default;

        bool loadFromFile(const std::string& path, std::string& texturePath, AnimationList& animations) override;

        bool saveToFile(const std::string& path,
                        const std::string& texturePath,
                        const robot2D::Color& maskColor,
                        const AnimationList& animationList,
                        robot2D::vec2f realTexturePos) override;
    private:
        enum class XmlKey {
            image,
            maskColor,
            head,
            animation,
            cut,
            title,
            delay,
            x_coord,
            y_coord,
            width,
            height
        };
        std::unordered_map<XmlKey, std::string> m_keys;
    };

    std::unique_ptr<IParser> getParser();
}