#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef RENDERER_HPP
    #define RENDERER_HPP

class Renderer {
private: 
    Shader shader = {"../src/shaders/vertex_shader.glsl", "../src/shaders/fragment_shader.glsl"};
    unsigned int VAO, VBO, EBO;
    const char* model_uniform_name = "model";

public:
    

    void init(const float* vertices, const unsigned int* indices);

    void update();
    void render(const glm::mat4 projection, const glm::vec3 pos, const float angle, const glm::vec3 axis, const glm::vec3 scale);
};

#endif