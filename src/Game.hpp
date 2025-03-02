#include "Tetromino_Renderer.hpp"
#include <GLFW/glfw3.h>

#ifndef GAME_HPP
#define GAME_HPP

enum GAME_STATE {
    MENU,
    RUNNING,
    PAUSED
};

class Game {
private:
    Shader shader;
    GAME_STATE state;

    unsigned int VAO;
    unsigned int EBO;

    int win_width = 800, win_height = 600;
    float frustum_width = 800, frustum_height = 600;

    float ratio;

    GLFWwindow* window;

    static void processInput(GLFWwindow* window);

public:
    Game(GLFWframebuffersizefun callback);

    void init();
    
    void render();
    void update();

    void run();
};

#endif