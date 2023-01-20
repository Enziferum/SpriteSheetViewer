#include <robot2D/Graphics/RenderTarget.hpp>
#include <viewer/ViewerView.hpp>

namespace viewer {

    void ViewerView::setup() {
        sheetAnimation.setAnimationRender( m_animatedSprite);

        robot2D::FrameBufferSpecification frameBufferSpecification;
        frameBufferSpecification.attachments =  {
                robot2D::FrameBufferTextureFormat::RGBA8
        };
        frameBufferSpecification.size = winSize.as<int>();
        m_frameBuffer = robot2D::FrameBuffer::Create(frameBufferSpecification);
    }

    void ViewerView::update(float dt) {
        sheetAnimation.update(dt);
    }

    void ViewerView::draw(robot2D::RenderTarget& target, robot2D::RenderStates) const {

        m_frameBuffer -> Bind();
        m_window -> clear(robot2D::Color::White);

        m_sceneGrid.render(m_camera2D.getCameraView(), m_window->getSize());

        m_window -> beforeRender();
        m_window -> setView(m_camera2D.getCameraView());

        m_window -> draw(m_sprite);
        if(m_currentAnimation >= 0)
            m_window -> draw(m_animations[m_currentAnimation]);

        if(m_leftMousePressed) {
            viewer::Collider debugCollider;
            debugCollider.setRect(movingAABB);
            debugCollider.borderColor = selectColor;
            m_window -> draw(debugCollider);
        }

        m_window -> afterRender();
        m_panelManager.render();
        m_frameBuffer -> unBind();
    }
}