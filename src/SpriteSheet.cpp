#include <memory>
#include <robot2D/Util/Logger.hpp>

#include <viewer/SpriteSheet.hpp>
#include "TinyXML/tinyxml.h"

namespace {
    constexpr char* headTag = "sprites";
    constexpr char* animationTag = "animation";
}

namespace viewer {

    class ILoader {
    public:
        virtual ~ILoader() = 0;
        virtual bool loadFromFile(const std::string& path, AnimationList& animations) = 0;
    };

    ILoader::~ILoader() {}

    class XmlLoader: public ILoader {
    public:
        ~XmlLoader() override = default;
        bool loadFromFile(const std::string& path, AnimationList& animations) override {
            const char* p = path.c_str();
            TiXmlDocument document(p);
            if (!document.LoadFile())
                return false;

            TiXmlElement* head = document.FirstChildElement(headTag);
            if(!head)
                return false;

            TiXmlElement* animation = head -> FirstChildElement(animationTag);
            if(!animation)
                return false;

            while(animation) {
                Animation anim;
                anim.title = animation -> Attribute("title");
                animation -> Attribute("delay", &anim.delay);
                std::cout << "Start Process animation := " << anim.title << " delay := " << anim.delay << std::endl;
                TiXmlElement* cut = animation -> FirstChildElement("cut");
                if(!cut)
                    return false;

                while (cut) {
                    robot2D::IntRect frame;
                    cut -> Attribute("x", &frame.lx);
                    cut -> Attribute("y", &frame.ly);
                    cut -> Attribute("w", &frame.width);
                    cut -> Attribute("h", &frame.height);
                    anim.frames.emplace_back(frame);
                    anim.flip_frames.emplace_back(robot2D::IntRect(frame.lx + frame.width, frame.ly, -frame.width,
                                                                   frame.height));
                    cut = cut->NextSiblingElement();
                }
                animation = animation -> NextSiblingElement();
                std::cout << "Animation reading finish, got " << anim.frames.size() << " frames" << std::endl;
                animations.emplace_back(anim);
            }

            return true;
        }
    };

    std::unique_ptr<ILoader> getLoader() {
        return std::make_unique<XmlLoader>();
    }

    SpriteSheet::SpriteSheet():m_animations() {}

    bool SpriteSheet::loadFromFile(const std::string& path) {

        auto loader = getLoader();
        if(!loader || !loader -> loadFromFile(path, m_animations))
            return false;

        return true;
    }

}
