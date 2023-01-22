#include <TinyXML/tinyxml.h>
#include <viewer/AnimationIO.hpp>

namespace viewer {
    namespace {
        constexpr char* headTag = "sprites";
        constexpr char* animationTag = "animation";
    }

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

    bool AnimationIO::saveToFile(const std::string& path,
                                 const std::string& texturePath,
                                 const robot2D::Color& maskColor,
                                 const AnimationList& animationList,
                                 robot2D::vec2f realTexturePos) {
        TiXmlDocument document{path.c_str()};

        TiXmlDeclaration* declaration = new TiXmlDeclaration{"1.0", "", "robot2D "};
        document.LinkEndChild(declaration);

        TiXmlElement* head = new TiXmlElement{headTag};
        head -> SetAttribute("image", texturePath.c_str());

        auto hexColor = colorToHex(maskColor.red, maskColor.green, maskColor.blue, maskColor.alpha);
        std::string hexColorStr = std::to_string(hexColor);
        head -> SetAttribute("maskColor", hexColorStr.c_str());

        for(const auto& anim: animationList) {
            TiXmlElement* animation = new TiXmlElement{animationTag};
            animation -> SetAttribute("title", anim.title.c_str());
            animation -> SetAttribute("delay", anim.delay);
            for(auto& frame: anim.frames) {
                TiXmlElement* cutElement = new TiXmlElement{"cut"};
                cutElement -> SetAttribute("x", frame.lx);
                cutElement -> SetAttribute("y", (frame.ly - realTexturePos.y));
                cutElement -> SetAttribute("w", frame.width);
                cutElement -> SetAttribute("h", frame.height);
                animation -> LinkEndChild(cutElement);
            }
            head -> LinkEndChild(animation);
        }
        document.LinkEndChild(head);

        if(!document.SaveFile())
            return false;

        return true;
    }
}