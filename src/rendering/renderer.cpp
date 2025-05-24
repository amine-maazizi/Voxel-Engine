#include "rendering/renderer.hpp"

Renderer::Renderer(GLFWwindow* window, bool wireframe) : window(window) {
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set polygon mode to wireframe
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set polygon mode to fill
    }
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
