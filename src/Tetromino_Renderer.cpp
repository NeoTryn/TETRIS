#include "Tetromino_Renderer.hpp"

Tetromino_Renderer::Tetromino_Renderer(unsigned int VAO, unsigned int EBO, Shader shader, float block_size, float ratio) {
    Tetromino_Renderer::VAO = VAO;
    Tetromino_Renderer::EBO = EBO;
    Tetromino_Renderer::shader = shader;
    Tetromino_Renderer::block_size = block_size;
    Tetromino_Renderer::ratio = ratio;
}

void Tetromino_Renderer::draw_tetromino(BLOCK_TYPE type) {
    Tetromino_Renderer::shader.use();
    glBindVertexArray(Tetromino_Renderer::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Tetromino_Renderer::EBO);

    for (int i = 0; i < 4; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));

        switch (type) {
            case BLOCK_TYPE::I:
                model = glm::translate(model, glm::vec3(0.0f, block_size * i, 0.0f));
                break;
            case BLOCK_TYPE::J:
                break;
            case BLOCK_TYPE::L:
                break;
            case BLOCK_TYPE::T:
                break;
            case BLOCK_TYPE::Z:
                break;
            case BLOCK_TYPE::S:
                break;
            case BLOCK_TYPE::O:
                break;
        }
        
        model = glm::scale(model, glm::vec3(Tetromino_Renderer::block_size / Tetromino_Renderer::ratio, Tetromino_Renderer::block_size, Tetromino_Renderer::block_size));
        glUniformMatrix4fv(glGetUniformLocation(Tetromino_Renderer::shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}