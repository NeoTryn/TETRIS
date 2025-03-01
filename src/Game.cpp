#include "Game.hpp"

Game::Game(GLFWframebuffersizefun callback) {
    Game::state = GAME_STATE::MENU;

    if (!glfwInit()) {
        std::cout << "GLFW couldn't initialize\n";
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    Game::window = glfwCreateWindow(Game::win_width, Game::win_height, "TETRIS TIME!!!", glfwGetPrimaryMonitor(), nullptr);

    if (!Game::window) {
        std::cout << "Window couldn't initialize...\n";
    }

    //glfwGetWindowSize(Game::window, &(Game::win_width), &(Game::win_height));

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    Game::win_width = mode->width;
    Game::win_height = mode->height;

    Game::ratio = static_cast<float>(Game::win_width / Game::win_height);

    std::cout << Game::win_width << " " << Game::win_height << "\n";

    glfwMakeContextCurrent(Game::window);
    glfwSetFramebufferSizeCallback(Game::window, callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD couldn't initialize...\n";
    }

    glViewport(0, 0, Game::win_width, Game::win_height);
    glClearColor(0.2f, 0.45f, 0.65f, 1.0f);

    Game::shader = {"../src/shaders/vertex_shader.glsl", "../src/shaders/fragment_shader.glsl"};
}

void Game::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Game::init() {
    unsigned int VBO;

    float vertices[] = {
        -0.5f,  0.5f, 0.0f, // upper left
        -0.5f, -0.5f, 0.0f, // lower left
         0.5f,  0.5f, 0.0f, // upper right
         0.5f, -0.5f, 0.0f  // lower right
    };

    unsigned int indices[] = {
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
    glfwSwapBuffers(Game::window);
    glfwPollEvents();

    Game::processInput(Game::window);
    glClear(GL_COLOR_BUFFER_BIT);

    Game::shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    std::cout << Game::win_width / Game::win_height << "\n";

    model = glm::scale(model, glm::vec3(1.0f / Game::ratio, 1.0f, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(Game::shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

void Game::run() {
    while (!glfwWindowShouldClose(Game::window)) {
        Game::update();
        Game::render();
    }
}