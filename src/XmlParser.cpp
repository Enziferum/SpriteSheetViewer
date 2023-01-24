#include <TinyXML/tinyxml.h>
#include <robot2D/Util/Logger.hpp>
#include <robot2D/Graphics/Color.hpp>

#include "XmlParser.hpp"

namespace viewer {

    unsigned long colorToHex(int r, int g, int b, int a)
    {
        return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
               + (a & 0xff);
    }

    robot2D::Color hexToColor(unsigned int hexValue) {
        robot2D::Color rgbColor;
        rgbColor.red = ((hexValue >> 24) & 0xFF);  // Extract the RR byte
        rgbColor.green = ((hexValue >> 16) & 0xFF);   // Extract the GG byte
        rgbColor.blue = ((hexValue >> 16) & 0xFF);   // Extract the BB byte
        rgbColor.alpha = ((hexValue) & 0xFF);        // Extract the alpha byte
        return rgbColor;
    }


    IParser::~IParser() {}

    XmlParser::XmlParser() {
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
    }

    bool XmlParser::loadFromFile(const std::string& path,
                                 std::string& texturePath,
                                 viewer::AnimationList& animations) {
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

    bool XmlParser::saveToFile(const std::string& path,
                               const std::string& texturePath,
                               const robot2D::Color& maskColor,
                               const viewer::AnimationList& animationList,
                               robot2D::vec2f realTexturePos) {
        TiXmlDocument document{path.c_str()};

        auto declaration = std::make_unique<TiXmlDeclaration>("1.0", "", "robot2D ");
        if(!declaration)
            return false;
        document.InsertEndChild(*declaration.get());

        auto head = std::make_unique<TiXmlElement>(m_keys[XmlKey::head].c_str());
        if(!head)
            return false;
        head -> SetAttribute(m_keys[XmlKey::image].c_str(), texturePath.c_str());

        auto hexColor = colorToHex(maskColor.red, maskColor.green, maskColor.blue, maskColor.alpha);
        std::string hexColorStr = std::to_string(hexColor);
        head -> SetAttribute(m_keys[XmlKey::maskColor].c_str(), hexColorStr.c_str());

        for(const auto& anim: animationList) {
            auto animation = std::make_unique<TiXmlElement>(m_keys[XmlKey::animation].c_str());
            if(!animation)
                return false;
            animation -> SetAttribute(m_keys[XmlKey::title].c_str(), anim.title.c_str());
            animation -> SetAttribute(m_keys[XmlKey::delay].c_str(), anim.delay);
            for(auto& frame: anim.frames) {
                auto cutElement = std::make_unique<TiXmlElement>(m_keys[XmlKey::cut].c_str());
                if(!cutElement)
                    return false;
                cutElement -> SetAttribute(m_keys[XmlKey::x_coord].c_str(), frame.lx);
                cutElement -> SetAttribute(m_keys[XmlKey::y_coord].c_str(), (frame.ly - realTexturePos.y));
                cutElement -> SetAttribute(m_keys[XmlKey::width].c_str(), frame.width);
                cutElement -> SetAttribute(m_keys[XmlKey::height].c_str(), frame.height);
                animation -> InsertEndChild(*cutElement.get());
            }
            head -> InsertEndChild(*animation.get());
        }
        document.InsertEndChild(*head.get());

        if(!document.SaveFile())
            return false;

        return true;
    }

    std::unique_ptr<IParser> getParser() {
        return std::make_unique<XmlParser>();
    }
}