#pragma once

#include "rendering/shader.hpp"

class Block {
    public:
        Block();
        ~Block();

        void render();

    private:
        int id;
        glm::vec3 position;

        // let's start with a triangel to make it easier
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO; 

        Shader shader;
};
