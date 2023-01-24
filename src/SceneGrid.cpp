#include <robot2D/Graphics/GL.hpp>
#include <robot2D/Util/Logger.hpp>
#include <viewer/SceneGrid.hpp>

#include <robot2D/Graphics/Transform.hpp>

namespace viewer {

    const std::string gridVertexShader = R"(
        #version 330 core
        layout (location = 0) in vec2 Position;
        layout (location = 1) in vec2 TexCoord;

        out vec2 fragCoord;
        uniform mat4 projectionMatrix;

        void main() {
            fragCoord = TexCoord;
            gl_Position = vec4(Position, 0, 1.0);
            gl_Position = sign(gl_Position);

            fragCoord = (vec2(gl_Position.x, gl_Position.y)
                         + vec2(1.0)) / vec2(2.0);
        }
    )";

    const std::string gridFragmentShader = R"(
        #version 450 core

        layout (location = 0) out vec4 fragColor;
        in vec2 fragCoord;

        const float cellSize = 128.0;

        // colors
        const vec4 col0 = vec4(0.5, 0.5, 0.5, 1.0);
        const vec4 col1 = vec4(0.7, 0.7, 0.7, 1.0);

        bool checkboard(vec2 textureCoords, vec2 scale) {
            float s = textureCoords.x;
            float t = textureCoords.y;

            float sum = floor(s * scale.x) + floor(t * scale.y);
            bool isEven = mod(sum, 2.0) == 0.0;
            return isEven;
        }

        void main() {
            vec2 scale = vec2(gl_FragCoord.x / cellSize, gl_FragCoord.y / cellSize);
            bool isEven = checkboard(fragCoord, vec2(cellSize, cellSize * 0.6));
            fragColor = isEven ? col0 : col1;
        }

    )";

    void SceneGrid::setGridElementSize(const size_t& size) {
        m_shader.use();
        m_shader.unUse();
    }

    void SceneGrid::setGridColors(const robot2D::Color &one, const robot2D::Color &two) {
        m_shader.use();
        m_shader.set("colorOne", one);
        m_shader.set("colorTwo", two);
        m_shader.unUse();
    }

    bool SceneGrid::setup() {
        if(!m_shader.createShader(robot2D::shaderType::vertex, gridVertexShader, false)){
            RB_ERROR("Can't setup Grid's vertex shader");
            return false;
        }

        if(!m_shader.createShader(robot2D::shaderType::fragment, gridFragmentShader, false)){
            RB_ERROR("Can't setup Grid's fragment shader");
            return false;
        }

        m_vertexArray = robot2D::VertexArray::Create();
        if(!m_vertexArray)
            return false;

        auto vertexBuffer = robot2D::VertexBuffer::Create(sizeof(Vertex) * 4);

        m_vertices[0].texCoord = {0, 0};
        m_vertices[1].texCoord = {1, 0};
        m_vertices[2].texCoord = {1, 1};
        m_vertices[3].texCoord = {0, 1};

        vertexBuffer -> setAttributeLayout( {
            { robot2D::ElementType::Float2, "Position"},
            { robot2D::ElementType::Float2, "TexCoord"}
        });

        uint32_t quadIndices[6];
        quadIndices[0] = 0;
        quadIndices[1] = 1;
        quadIndices[2] = 2;
        quadIndices[3] = 2;
        quadIndices[4] = 3;
        quadIndices[5] = 0;

        auto indexBuffer = robot2D::IndexBuffer::Create(quadIndices, 6 * sizeof(uint32_t));
        m_vertexArray -> setVertexBuffer(vertexBuffer);
        m_vertexArray -> setIndexBuffer(indexBuffer);

        m_vertices[0].pos = robot2D::vec2f {-1.F, -1.F};
        m_vertices[1].pos = robot2D::vec2f {1.F, -1.F};
        m_vertices[2].pos = robot2D::vec2f {1.F, 1.F};
        m_vertices[3].pos = robot2D::vec2f {-1.F, 1.F};

        return true;
    }

    void SceneGrid::render() const{
        m_shader.use();

        m_vertexArray -> getVertexBuffer() -> setData(&m_vertices[0], sizeof(Vertex) * 4);

        m_vertexArray -> Bind();
        auto indicesSize = m_vertexArray -> getIndexBuffer() -> getSize() / 4;
        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
        m_vertexArray -> unBind();

        m_shader.unUse();
    }
} // namespace viewer