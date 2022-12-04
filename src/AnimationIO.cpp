#include <TinyXML/tinyxml.h>
#include <viewer/AnimationIO.hpp>

namespace viewer {
    namespace {
        constexpr char* headTag = "sprites";
        constexpr char* animationTag = "animation";
    }

    bool AnimationIO::saveToFile(const std::string& path, const AnimationList& animationList,
                                 robot2D::vec2f realTexturePos) {
        TiXmlDocument document{path.c_str()};

        TiXmlDeclaration* declaration = new TiXmlDeclaration{"1.0", "", "robot2D "};
        document.LinkEndChild(declaration);

        TiXmlElement* head = new TiXmlElement{headTag};
        head -> SetAttribute("image", "BossWalk.png");
        for(auto& it: animationList) {
            TiXmlElement* animation = new TiXmlElement{animationTag};
            animation -> SetAttribute("title", it.title.c_str());
            animation -> SetAttribute("delay", it.delay);
            for(auto& frame: it.frames) {
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