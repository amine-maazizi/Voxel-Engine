#include "core/engine.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* Engine, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // getting camera instance from user pointer
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->camera.processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    } else {
        std::cerr << "Failed to get Engine instance from window user pointer." << std::endl;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    // Getting camera instance from user pointer
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->camera.processMouseScroll(static_cast<float>(yoffset));
    } else {
        std::cerr << "Failed to get Engine instance from window user pointer." << std::endl;
    }
}


Engine::Engine(bool wireframe) : wireframe(wireframe) {
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

    window = glfwCreateWindow(800, 600, "VoxelEngine", NULL, NULL);
    if (window == NULL) {
        const char* description;
        int code = glfwGetError(&description);
        std::cerr << "Failed to create GLFW Window. Error Code: " << code << ", Description: " << description << std::endl;
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    glfwSetWindowUserPointer(window, this); // Set the user pointer to this instance
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Set polygon mode to wireframe
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Set polygon mode to fill
    }
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering


    camera = Camera();

    block = new Block(); // Initialize the block object
    if (!block) {
        std::cerr << "Failed to create Block object" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(-1);
    }
}

Engine::~Engine() {
    delete block; // Clean up the block object
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::renderBlock(glm::vec3 position, glm::vec3 rotation) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    block->update(model, view, projection);
    block->render();
}

void Engine::processInput(float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    camera.processInput(dt); // Process camera input for movement
}

void Engine::update() {
    float dt = 0.0f; 
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        processInput(dt);
        camera.update(); // Update camera position and direction
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < blockCount; ++i) {
        renderBlock(blockPositions[i]);
    }
}