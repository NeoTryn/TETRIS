#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 proj;

void main() {
    gl_Position = proj * model * vec4(pos, 1.0);
}