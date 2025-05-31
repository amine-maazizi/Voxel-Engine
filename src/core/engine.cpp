#include "core/engine.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* Engine, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->camera.processMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
    } else {
        std::cerr << "Failed to get Engine instance from window user pointer." << std::endl;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if (engine) {
        engine->camera.processMouseScroll(static_cast<float>(yoffset));
    } else {
        std::cerr << "Failed to get Engine instance from window user pointer." << std::endl;
    }
}

Engine::Engine(bool wireframe, glm::vec3 chunkSize) 
    : wireframe(wireframe), chunkSize(chunkSize), CHUNK_THRESHOLD(8.0f) {
    
    if (!glfwInit()) {
        const char* description;
        glfwGetError(&description);
        std::cerr << "GLFW Init Failed: " << description << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "VoxelEngine", NULL, NULL);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glEnable(GL_DEPTH_TEST);
    camera = Camera();

    chunkPosition = glm::ivec3(0, 0, 0);
    currentChunk = new Chunk(chunkPosition, chunkSize);
    currentChunk->generate();
    currentChunk->assembleMesh();
}

Engine::~Engine() {
    delete currentChunk;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Engine::generateChunk() {
    delete currentChunk;
    currentChunk = new Chunk(chunkPosition, chunkSize);
    currentChunk->generate();
    currentChunk->assembleMesh();
}

void Engine::processInput(float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    camera.processInput(dt);
}

void Engine::update() {
    float dt = 0.0f; 
    float lastTime = glfwGetTime();
    
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastTime;
        lastTime = currentTime;

        bool needNewChunk = false;
        glm::ivec3 newChunkPosition = chunkPosition;
        
        // Calculate chunk boundaries based on actual chunk sizes
        int cameraChunkX = static_cast<int>(std::floor(camera.position.x / chunkSize.x)) * static_cast<int>(chunkSize.x);
        int cameraChunkZ = static_cast<int>(std::floor(camera.position.z / chunkSize.z)) * static_cast<int>(chunkSize.z);
        
        if (cameraChunkX != chunkPosition.x || cameraChunkZ != chunkPosition.z) {
            newChunkPosition.x = cameraChunkX;
            newChunkPosition.z = cameraChunkZ;
            needNewChunk = true;
        }
        
        if (needNewChunk) {
            chunkPosition = newChunkPosition;
            generateChunk();
            std::cout << "Generated new chunk at: " << chunkPosition.x << ", " << chunkPosition.z 
                      << " (size: " << chunkSize.x << "x" << chunkSize.y << "x" << chunkSize.z << ")" << std::endl;
        }

        processInput(dt);
        camera.update();
        
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::render() {
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up matrices
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), 
                                          (float)WIDTH / (float)HEIGHT, 
                                          0.1f, 100.0f);

    // Update chunk with matrices
    currentChunk->update(model, view, projection);
    
    // Render the chunk
    currentChunk->render();
}