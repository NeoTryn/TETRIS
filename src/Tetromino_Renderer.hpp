#include "Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef TETROMINO_RENDERER_HPP
#define TETROMINO_RENDERER_HPP

enum BLOCK_TYPE {
    I,
    J,
    L,
    O,
    T,
    S,
    Z
};

class Tetromino_Renderer {
private:
    unsigned int VAO, EBO;
    Shader shader;
    float block_size, ratio;

public:
    Tetromino_Renderer() = default;
    Tetromino_Renderer(unsigned int VAO, unsigned int EBO, Shader shader, float block_size, float ratio);

    void draw_tetromino(BLOCK_TYPE type);
};

#endif