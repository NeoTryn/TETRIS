#include "Shader.hpp"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

int win_width = 800, win_height = 600;

// the ratio is used to get the vertices to a square shape
float ratio = static_cast<float>(win_width) / static_cast<float>(win_height);

float vertices[] = {
    -0.5f / ratio,  0.5f, 0.0f,
    -0.5f / ratio, -0.5f, 0.0f,
     0.5f / ratio,  0.5f, 0.0f,
     0.5f / ratio, -0.5f, 0.0f  
};

const unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // calculate new ration based on new window width and height
    const float new_ratio = static_cast<float>(width) / static_cast<float>(height);
    
    // iterate through vertices jumping over the y and z coordinates
    for (int i = 0; i < (sizeof(vertices) / sizeof(*vertices)); i += 3) {
        // multiply the x coordinate by the old ratio so we get back the normal value
        vertices[i] *= ratio;
        // divide it by the new ratio so it adjusts to new window size
        vertices[i] /= new_ratio;
    }

    // set ratio, win_width and win_height to the new values
    ratio = new_ratio;
    win_width = width, win_height = height;

    // update VBO data with the vertices array newly adjusted to the window size
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    std::cout << ratio;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(win_width, win_height, "Tetris Time!!!", NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    Shader shader = {"../src/shaders/vertex_shader.glsl", "../src/shaders/fragment_shader.glsl"};

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.0f, 0.0f));
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSwapBuffers(window);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUniformMatrix4fv(glGetUniformLocation(shader.programId, "trans"), 1, GL_FALSE, glm::value_ptr(trans));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}