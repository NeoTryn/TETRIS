#include "Renderer.hpp"

void Renderer::init(const float* vertices, const unsigned int* indices) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
}

void Renderer::render(const glm::mat4 projection, const glm::vec3 pos, const float angle, const glm::vec3 axis, const glm::vec3 scale) {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, pos);
    
    if (angle != 0) model = glm::rotate(model, angle, axis);

    model = glm::scale(model, scale);

    Renderer::shader.use();

    glUniformMatrix4fv(glGetUniformLocation(Renderer::shader.programId, Renderer::model_uniform_name), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(Renderer::shader.programId, "proj"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(Renderer::VAO);
    glBindBuffer(1, Renderer::EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}