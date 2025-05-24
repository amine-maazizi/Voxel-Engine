#include <iostream>
#include <stdlib.h>

#include "renderer.hpp"



class Window {
    public:
        Window();
        ~Window();

        void update();
        void processInput();
        
    private:
        GLFWwindow* window;
        Renderer* renderer;
};

