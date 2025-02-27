#include "Shader.hpp"
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

    unsigned short win_width = 800, win_height = 600;
    float frustum_width = 800, frustum_height = 600;

    GLFWwindow* window;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);

public:
    Game(const char* vertPath, const char* fragPath);

    void init();
    
    void render();
    void update();
    void clear();

    void run();
};

#endif