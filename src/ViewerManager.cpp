#include <viewer/ViewerManager.hpp>
#include <viewer/commands/AddFrameCommand.hpp>
#include <viewer/commands/DeleteFrameCommand.hpp>

namespace viewer {
    ViewerManager::ViewerManager(robot2D::MessageBus& messageBus,
                                 MessageDispatcher& messageDispatcher):
                                 m_messageBus{messageBus},
                                 m_messageDispatcher{messageDispatcher}
    {}


    void ViewerManager::setupMessages() {
        m_messageDispatcher.onMessage<AddAnimationMessage>(MessageID::AddAnimation,
                                                           BIND_CLASS_FN(onAddAnimation));

        m_messageDispatcher.onMessage<SwitchAnimationMessage>(MessageID::SwitchAnimation,
                                                              BIND_CLASS_FN(onSwitchAnimation));


        m_messageDispatcher.onMessage<SaveAnimationsMessage>(MessageID::SaveAnimations,
                                                             BIND_CLASS_FN(onSaveAnimations));

        m_messageDispatcher.onMessage<DeleteAnimationMessage>(MessageID::DeleteAnimation,
                                                              BIND_CLASS_FN(onDeleteAnimation));

        m_messageDispatcher.onMessage<LoadImageMessage>(MessageID::LoadImage, BIND_CLASS_FN(onLoadImage));

        m_messageDispatcher.onMessage<LoadXmlMessage>(MessageID::LoadXml, BIND_CLASS_FN(onLoadXml));
    }


    void ViewerManager::onAddAnimation(const AddAnimationMessage& message) {
        ViewerAnimation viewerAnimation{};
        viewerAnimation.getAnimation().title = message.name;
        m_animations.emplace_back(std::move(viewerAnimation));
        m_currentAnimation = m_animations.size() - 1;

        auto& viewerPanel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = viewerPanel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerManager::onSaveAnimations(const SaveAnimationsMessage& message) {
        AnimationIO animationIo{};
        AnimationList animations;
        for(const auto& animation: m_animations)
            animations.emplace_back(animation.getAnimation());
        if(!animationIo.saveToFile(message.filePath, animations)) {
            RB_ERROR("Can't save animation");
        }
    }

    void ViewerManager::onDeleteAnimation(const DeleteAnimationMessage& message) {
        assert(message.deleteIndex < m_animations.size());
        m_animations.erase(m_animations.begin() + message.deleteIndex);
        m_currentAnimation = message.switchToIndex;

        auto& panel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = panel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerManager::onSwitchAnimation(const SwitchAnimationMessage& message) {
        m_currentAnimation = message.indexTo;
        auto& panel = m_panelManager.getPanel<ViewerPanel>();
        auto* sheet = panel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerManager::onLoadImage(const LoadImageMessage& message) {
        if(!m_texture.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load texture by path: {0}", message.filePath);
            return;
        }

        auto& textureSize = m_texture.getSize();
        m_animatedSprite.setTexture(m_texture, {0, 0,
                                                static_cast<int>(textureSize.x),
                                                static_cast<int>(textureSize.y)});

        auto&& bounds = m_animatedSprite.getGlobalBounds();
        auto windowSize = m_frameBuffer -> getSpecification().size;

        robot2D::vec2f spritePosition = {
                windowSize.x / 2.F - bounds.width / 2.F,
                windowSize.y / 2.F - bounds.height / 2.F
        };

        m_animatedSprite.setPosition(spritePosition);
        m_sprite = m_animatedSprite;
    }

    void ViewerManager::onLoadXml(const LoadXmlMessage& message) {
        m_currentAnimation = 0;
        m_animations.clear();
        sheetAnimation.reset();
        m_spriteSheet.removeAll();

        if(!m_spriteSheet.loadFromFile(message.filePath)) {
            RB_ERROR("Can't load sprite sheet by path: {0}", message.filePath);
            return;
        }

        fs::path path{message.filePath};
        path.remove_filename();
        path.assign(m_spriteSheet.getTexturePath());

        if(!m_texture.loadFromFile(path.string())) {
            RB_ERROR("Can't load texture by path: {0}", message.filePath);
            return;
        }

        auto& textureSize = m_texture.getSize();
        m_animatedSprite.setTexture(m_texture, {0, 0,
                                                static_cast<int>(textureSize.x),
                                                static_cast<int>(textureSize.y)});

        auto&& bounds = m_animatedSprite.getGlobalBounds();
        auto windowSize = m_frameBuffer -> getSpecification().size;

        robot2D::vec2f spritePosition = {
                windowSize.x / 2.F - bounds.width / 2.F,
                windowSize.y / 2.F - bounds.height / 2.F
        };

        m_animatedSprite.setPosition(spritePosition);
        m_sprite = m_animatedSprite;

        m_messageBus.postMessage<bool>(MessageID::AnimationPanelLoadXml);
        for(const auto& animation: m_spriteSheet.getAnimations()) {
            m_animations.emplace_back(ViewerAnimation{animation, spritePosition});
            auto* msg = m_messageBus.postMessage<AnimationPanelLoadMessage>(MessageID::AnimationPanelAddAnimation);
            msg -> name = animation.title;
        }

        auto& viewerPanel = m_panelManager.getPanel<ViewerPanel>();
        auto& animationPanel = m_panelManager.getPanel<AnimationPanel>();
        auto* sheet = viewerPanel.getSpriteSheetAnimation();
        if(sheet)
            sheet -> setAnimation(m_animations[m_currentAnimation].getAnimation());
    }

    void ViewerManager::undo() {
        m_commandStack.undo();
    }

    void ViewerManager::redo() {
        m_commandStack.redo();
    }

} // namespace viewer