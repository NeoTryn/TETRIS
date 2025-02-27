#include "Game.hpp"

Game::Game(const char* vertPath, const char* fragPath) {
    Game::shader = { vertPath, fragPath };
    Game::state = GAME_STATE::MENU;

    if (!glfwInit()) {
        std::cerr << "GLFW couldn't initialize\n";
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Game::init() {
    unsigned int VBO;

    const float vertices[] = {
        -0.5f,  0.5f, 0.0f, // upper left
        -0.5f, -0.5f, 0.0f, // lower left
         0.5f,  0.5f, 0.0f, // upper right
         0.5f, -0.5f, 0.0f  // lower right
    };

    const unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &(Game::VAO));
    glBindVertexArray(Game::VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &VBO);
}

void Game::render() {
    Game::shader.use();

    glBindVertexArray(Game::VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::EBO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::update() {
    std::cout << "Updating\n";
}

void Game::clear() {
    std::cout << "Clearing\n";
}

void Game::run() {

}