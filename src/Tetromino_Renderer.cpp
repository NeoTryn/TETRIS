#include "Tetromino_Renderer.hpp"

Tetromino_Renderer::Tetromino_Renderer(unsigned int VAO, unsigned int EBO, Shader shader, float block_size, float ratio, float frustum_width, float frustum_height) {
    Tetromino_Renderer::VAO = VAO;
    Tetromino_Renderer::EBO = EBO;
    Tetromino_Renderer::shader = shader;
    Tetromino_Renderer::block_size = block_size;
    Tetromino_Renderer::ratio = ratio;
    Tetromino_Renderer::frustum_width = frustum_width;
    Tetromino_Renderer::frustum_height = frustum_height;
    Tetromino_Renderer::field_width = 10;
    Tetromino_Renderer::field_height = 20;
}

void Tetromino_Renderer::draw_tetromino(BLOCK_TYPE type, glm::vec3 pos, float angle, glm::vec3 axis) {
    Tetromino_Renderer::shader.use();
    glBindVertexArray(Tetromino_Renderer::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Tetromino_Renderer::EBO);

    const float block_size_x = Tetromino_Renderer::block_size / Tetromino_Renderer::ratio;

    for (int i = 0; i < 4; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, pos);

        switch (type) {
            case BLOCK_TYPE::I:
                model = glm::translate(model, glm::vec3(0.0f, block_size * i, 0.0f));
                break;
            case BLOCK_TYPE::J:
                if (i != 0) {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 1), block_size, 0.0f));
                }
                break;
            case BLOCK_TYPE::L:
                if (i == 3) {
                    model = glm::translate(model ,glm::vec3(block_size_x * (i - 1), 0.0f, 0.0f));
                }
                else {
                    model = glm::translate(model, glm::vec3(block_size_x * i, block_size, 0.0f));
                }
                break;
            case BLOCK_TYPE::T:
                if (i == 2) {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 1), 0.0f, 0.0f));
                }
                else if (i == 3) {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 1), block_size, 0.0f));
                }
                else {
                    model = glm::translate(model, glm::vec3(block_size_x * i, block_size, 0.0f));
                }
                break;
            case BLOCK_TYPE::Z:
                if (i == 2 || i == 3) {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 1), block_size, 0.0f));
                }
                else {
                    model = glm::translate(model, glm::vec3(block_size_x * i, 0.0f, 0.0f));
                }
                break;
            case BLOCK_TYPE::S:
                if (i == 2 || i == 3) {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 1), 0.0f, 0.0f));
                }
                else {
                    model = glm::translate(model, glm::vec3(block_size_x * i, block_size, 0.0f));
                }
                break;
            case BLOCK_TYPE::O:
                if (i == 0 || i == 1) {
                    model = glm::translate(model, glm::vec3(block_size_x * i, 0.0f, 0.0f));
                }
                else {
                    model = glm::translate(model, glm::vec3(block_size_x * (i - 2), block_size, 0.0f));
                }
                break;
        }

        if (angle != 0.0f) {
            model = glm::rotate(model, angle, axis);
        }
        
        model = glm::scale(model, glm::vec3(Tetromino_Renderer::block_size / Tetromino_Renderer::ratio, Tetromino_Renderer::block_size, Tetromino_Renderer::block_size));
        glUniformMatrix4fv(glGetUniformLocation(Tetromino_Renderer::shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glm::vec3 block_color = glm::vec3(0.2f, 0.8f, 0.4f);

        glUniform3fv(glGetUniformLocation(Tetromino_Renderer::shader.programId, "color"), 1, glm::value_ptr(block_color));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

void Tetromino_Renderer::draw_field() {
    Tetromino_Renderer::shader.use();
    glBindVertexArray(Tetromino_Renderer::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Tetromino_Renderer::EBO);
    const float block_size_x = Tetromino_Renderer::block_size / Tetromino_Renderer::ratio;
    const float x_start = (Tetromino_Renderer::frustum_width - Tetromino_Renderer::field_width * block_size_x) / 2;
    const float y_start = (Tetromino_Renderer::frustum_height - Tetromino_Renderer::field_height * block_size) / 2;

    for (int i = 0; i < (Tetromino_Renderer::field_width); i++) {
        for (int j = 0; j < (Tetromino_Renderer::field_height); j++) {
            glm::mat4 model = glm::mat4(1.0f);

            model = glm::translate(model, glm::vec3(x_start, y_start, -0.5f));
            model = glm::translate(model, glm::vec3(block_size_x * i, block_size * j, 0.0f));

            model = glm::scale(model, glm::vec3(Tetromino_Renderer::block_size / Tetromino_Renderer::ratio, Tetromino_Renderer::block_size, Tetromino_Renderer::block_size));

            glUniformMatrix4fv(glGetUniformLocation(Tetromino_Renderer::shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
            
            glm::vec3 field_color = glm::vec3(0.7f, 0.7f, 0.7f);

            glUniform3fv(glGetUniformLocation(Tetromino_Renderer::shader.programId, "color"), 1, glm::value_ptr(field_color));

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        } 
    }
}