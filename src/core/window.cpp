#include "core/Window.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window() {
    if (!glfwInit()) {
        const char* description;
        glfwGetError(&description);
        std::cerr << "GLFW Init Failed: " << description << std::endl;
        exit(-1);
    }

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cerr << "GLFW Version: " << major << "." << minor << "." << rev << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Voxel Engine", NULL, NULL);
    if (window == NULL) {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "Failed to create GLFW window. Error Code: " << code << ", Description: " << description << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(-1);
    }

    std::cerr << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    renderer = new Renderer(window);

    // Initialize blocks
    blocks = new Block[1]; // For now, just one block
    if (!blocks) {
        std::cerr << "Failed to allocate memory for blocks" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(-1);
    }
}

Window::~Window() {
    delete[] blocks; // Clean up blocks
    delete renderer;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Window::update() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        renderer->render(blocks, 1); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}