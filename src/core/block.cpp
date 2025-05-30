#include "core/block.hpp"

Block::Block() {
    // Define cube vertices and indices
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  // 0
        0.5f, -0.5f, -0.5f,   // 1
        0.5f,  0.5f, -0.5f,   // 2
        -0.5f,  0.5f, -0.5f,  // 3
        -0.5f, -0.5f,  0.5f,  // 4
        0.5f, -0.5f,  0.5f,   // 5
        0.5f,  0.5f,  0.5f,   // 6
        -0.5f,  0.5f,  0.5f   // 7
    };

    unsigned int indices[] = {
        0, 1, 2,  2, 3, 0,  // back
        4, 5, 6,  6, 7, 4,  // front
        4, 7, 3,  3, 0, 4,  // left
        1, 5, 6,  6, 2, 1,  // right
        4, 5, 1,  1, 0, 4,  // bottom
        3, 2, 6,  6, 7, 3   // top
    };

    // Set up OpenGL resources
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Block::~Block() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO); // Clean up EBO
}

void Block::update(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    shader.use(); // Activate shader before setting uniforms
    shader.setMat4("model", modelMatrix);
    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", projectionMatrix);
}

void Block::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

