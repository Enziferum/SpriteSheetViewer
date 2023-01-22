#pragma once

#include <robot2D/Graphics/Shader.hpp>
#include <robot2D/Graphics/Color.hpp>
#include <robot2D/Graphics/View.hpp>
#include <robot2D/Graphics/VertexArray.hpp>


namespace viewer {

    struct Vertex {
        robot2D::vec2f pos;
        robot2D::vec2f texCoord;

        Vertex():pos{}, texCoord{}{}
        Vertex(robot2D::vec2f p, robot2D::vec2f t):pos{p}, texCoord{t}{};
    };

    class SceneGrid {
    public:
        SceneGrid() = default;
        ~SceneGrid() = default;

        void setGridElementSize(const std::size_t& size);
        void setGridColors(const robot2D::Color& one, const robot2D::Color& two);

        bool setup();
        void render() const;
    private:
        robot2D::ShaderHandler m_shader{};
        robot2D::Color m_one{};
        robot2D::Color m_two{};

        robot2D::VertexArray::Ptr m_vertexArray{nullptr};

        std::array<Vertex, 4> m_vertices;
    };
} // namespace viewer