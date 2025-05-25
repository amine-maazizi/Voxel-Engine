#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "rendering/shader.hpp"
#include "core/camera.hpp"

class Block {
    public:
        Block();
        ~Block();
        void render();
        void update(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    private:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO; 
        Shader shader;
};

