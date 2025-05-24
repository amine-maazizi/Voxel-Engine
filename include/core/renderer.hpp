#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

class Renderer {
    public:
        Renderer(GLFWwindow* window);
        ~Renderer();

        void render();
        
    private:
        GLFWwindow* window;
};

