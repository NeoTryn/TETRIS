#include "Game.hpp"

#include <iostream>

int main() {

    Game game = { "../src/shaders/vertex_shader.glsl", "../src/shaders/fragment_shaders.glsl" };

    game.init();

    game.run();

    return 0;
}