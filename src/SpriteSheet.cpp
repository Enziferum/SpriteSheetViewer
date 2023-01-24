#include <memory>
#include <robot2D/Util/Logger.hpp>

#include <viewer/SpriteSheet.hpp>
#include "TinyXML/tinyxml.h"

namespace viewer {

    class ILoader {
    public:
        virtual ~ILoader() = 0;
        virtual bool loadFromFile(const std::string& path, std::string& texturePath, AnimationList& animations) = 0;
    };

    ILoader::~ILoader() {}

    class XmlLoader: public ILoader {
    public:
        ~XmlLoader() override = default;

        bool loadFromFile(const std::string& path, std::string& texturePath, AnimationList& animations) override {

            m_keys = {
                    { XmlKey::image, "image"},
                    { XmlKey::maskColor, "maskColor"},
                    { XmlKey::title, "title"},
                    { XmlKey::delay, "delay"},
                    { XmlKey::head, "sprites"},
                    { XmlKey::cut, "cut"},
                    { XmlKey::animation, "animation"},
                    { XmlKey::x_coord, "x"},
                    { XmlKey::y_coord, "y"},
                    { XmlKey::width, "w"},
                    { XmlKey::height, "h"},
            };

            const char* p = path.c_str();
            TiXmlDocument document(p);
            if (!document.LoadFile())
                return false;

            TiXmlElement* head = document.FirstChildElement(m_keys[XmlKey::head].c_str());
            if(!head)
                return false;

            texturePath = head -> Attribute(m_keys[XmlKey::image].c_str());
            std::string maskColor = head -> Attribute(m_keys[XmlKey::maskColor].c_str());

            TiXmlElement* animation = head -> FirstChildElement(m_keys[XmlKey::animation].c_str());
            if(!animation)
                return false;

            while(animation) {
                Animation anim;
                anim.title = animation -> Attribute(m_keys[XmlKey::title].c_str());
                animation -> Attribute(m_keys[XmlKey::delay].c_str(), &anim.delay);
                RB_INFO("Start process animation, title: {0}, delay: {1}", anim.title, anim.delay);

                TiXmlElement* cut = animation -> FirstChildElement(m_keys[XmlKey::cut].c_str());
                if(!cut)
                    return false;

                while (cut) {
                    robot2D::IntRect frame;
                    cut -> Attribute(m_keys[XmlKey::x_coord].c_str(), &frame.lx);
                    cut -> Attribute(m_keys[XmlKey::y_coord].c_str(), &frame.ly);
                    cut -> Attribute(m_keys[XmlKey::width].c_str(), &frame.width);
                    cut -> Attribute(m_keys[XmlKey::height].c_str(), &frame.height);
                    anim.frames.emplace_back(frame);
                    anim.flip_frames.emplace_back(robot2D::IntRect(frame.lx + frame.width, frame.ly, -frame.width,
                                                                   frame.height));
                    cut = cut->NextSiblingElement();
                }
                animation = animation -> NextSiblingElement();
                RB_INFO("Animation reading finish, got : {0} frames", anim.frames.size());
                animations.emplace_back(anim);
            }

            return true;
        }
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

    std::unique_ptr<ILoader> getLoader() {
        return std::make_unique<XmlLoader>();
    }

    SpriteSheet::SpriteSheet():m_animations{} {}

    bool SpriteSheet::loadFromFile(const std::string& path) {

        auto loader = getLoader();
        if(!loader || !loader -> loadFromFile(path, m_texturePath, m_animations))
            return false;

        return true;
    }

} // namespace viewer
