#include "core/renderer.hpp"

Renderer::Renderer(GLFWwindow* window) : window(window) {
}

Renderer::~Renderer() {
}

void Renderer::render() {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
