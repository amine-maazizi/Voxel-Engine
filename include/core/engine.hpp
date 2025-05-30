#pragma once

#include <iostream>
#include <stdlib.h>

#include "core/block.hpp"
#include "core/camera.hpp"
#include "rendering/perlin_noise.hpp"

class Engine {
    public:
        Engine(bool, int chunkSize);
        Engine() : Engine(false, 16) {} // Default constructor with wireframe set to false
         ~Engine();

        void update();
        void render();
        void processInput(float);

        void renderBlock(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f));
    private:
        GLFWwindow* window;

        Block* block;

        bool wireframe;
        int chunkSize;

        BlockData* blockData;
    public:
        Camera camera;

};

