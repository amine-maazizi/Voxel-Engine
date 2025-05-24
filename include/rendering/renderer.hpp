#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

#include "core/block.hpp"

class Renderer {
    public:
        Renderer(GLFWwindow* window, bool wireframe = false);
        ~Renderer();

        void render(Block* blocks, int blockCount);
        
    private:
        GLFWwindow* window;
};

