#include "shader.h"
#include "texture.h"

namespace wind {
    namespace renderer {
        struct Mesh {
        private:
            struct Vertex {
                vec3 position;
                vec2 tex_coords;
            };
        private:
            uint m_VAO, m_VBO, m_EBO;
            vector<Vertex> m_vertices;
            vector<uint> m_indices;

            Shader* m_shader = nullptr;

        public:
            Mesh(vector<vec3> vertices, vector<uint> indicies, vector<vec2> uv, Shader* shader);
            ~Mesh();

            uint VAO() const;
            uint size() const;  

            Shader* shader() const;
        };
    }
}