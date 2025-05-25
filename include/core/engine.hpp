#pragma once

#include <iostream>
#include <stdlib.h>

#include "core/block.hpp"
#include "core/camera.hpp"


class Engine {
    public:
        Engine(bool);
        Engine() : Engine(false) {} // Default constructor with wireframe set to false
         ~Engine();

        void update();
        void render();
        void processInput(float);

        void renderBlock(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));
    private:
        GLFWwindow* window;
        Camera camera;

        Block* block;

        bool wireframe;

        // Block array
        static const int blockCount = 6; // Number of blocks to render
        glm::vec3 blockPositions[6] = {
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(2.0f, 0.0f, -5.0f),
            glm::vec3(-2.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 2.0f, -5.0f),
            glm::vec3(0.0f, -2.0f, -5.0f),
            glm::vec3(1.0f, 1.0f, -5.0f)
        };
};

