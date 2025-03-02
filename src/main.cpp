#include "Game.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {

    Game game = { framebuffer_size_callback };

    game.init();

    game.run();

    return 0;
}