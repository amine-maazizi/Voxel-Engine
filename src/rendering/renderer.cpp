#include "rendering/renderer.hpp"

Renderer::Renderer(GLFWwindow* window) : window(window) {
}

Renderer::~Renderer() {
}

void Renderer::render(Block* blocks, int blockCount) {
    glClearColor(.5f, .0f, .5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < blockCount; ++i) {
        blocks[i].render();
    }
}
