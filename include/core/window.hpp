#pragma once

#include <iostream>
#include <stdlib.h>

#include "rendering/renderer.hpp"
#include "core/block.hpp"


class Window {
    public:
        Window();
        ~Window();

        void update();
        void processInput();
        
    private:
        GLFWwindow* window;
        Renderer* renderer;

        // Block array
        Block* blocks;
};

