#include "Renderer.hpp"
#include <GLFW/glfw3.h>

#include <iostream>

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float win_width, win_height;
const float frustum_width = 800.0f, frustum_height = 600.0f;

float ratio;

const float vertices[] = {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

const unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};

int main() {

    if (!glfwInit()) {
        std::cerr << "GLFW couldn't initialize...\n";
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    win_width = mode->width;
    win_height = mode->height;

    GLFWwindow* window = glfwCreateWindow(win_width, win_height, "TETRIS TIME!!!", glfwGetPrimaryMonitor(), NULL);

    if (!window) {
        std::cerr << "GLFW window couldn't initialize...\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::cout << win_width << " " << win_height << "\n";

    ratio = frustum_width / frustum_height;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD couldn't initialize...\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, win_width, win_height);

    glClearColor(0.0f, 0.4f, 0.6f, 1.0f);

    /*Shader shader("../src/shaders/vertex_shader.glsl", "../src/shaders/fragment_shader.glsl");

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);*/

    //glBindVertexArray(0);
    /*glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

    glm::mat4 model = glm::mat4(1.0f), projection = glm::mat4(1.0f), view = glm::mat4(1.0f);

    projection = glm::ortho(0.0f, frustum_width, frustum_height, 0.0f, -1.0f, 1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    //projection = glm::perspective(glm::radians(90.0f), win_width / win_height, 0.1f, 100.0f);

    model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));

    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));

    model = glm::scale(model, glm::vec3(1 / ratio, 1.0f, 1.0f));

    Renderer renderer;
    renderer.init(vertices, indices);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        /*shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

        renderer.render(projection, glm::vec3(400.0f, 300.0f, 0.0f), 0.0f, glm::vec3(0.0f), glm::vec3(20.0f / ratio, 20.0f, 20.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    win_width = width, win_height = height;
}