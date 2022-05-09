#pragma once

#include <cstdint>
#include <memory>

#include "SpriteSheetAnimation.hpp"

using PanelID = uint32_t;

enum PanelIDS {
    MenuPanelID = 0,
    EntityComponentID,
    ViewerPanelID
};

class IPanel {
public:
    using Ptr = std::shared_ptr<IPanel>;
public:
    IPanel(const PanelID& id);
    virtual ~IPanel() = 0;

    virtual void update(float dt) = 0;
protected:
    PanelID m_id;
};

class MenuPanel: public IPanel {
public:
    MenuPanel();
    ~MenuPanel() override = default;

    void update(float dt) override;
    void setSpriteSheetAnimation(const SpriteSheetAnimation* spriteSheet) {
        m_animation = spriteSheet;
    }
private:
    void showFileMenu();
    const SpriteSheetAnimation* m_animation;
};

class ViewerPanel: public IPanel {
public:
    ViewerPanel();
    ~ViewerPanel() override = default;


    void setSpriteSheetAnimation(SpriteSheetAnimation* spriteSheet);
    void update(float dt) override;
private:
    SpriteSheetAnimation* m_animation;
};