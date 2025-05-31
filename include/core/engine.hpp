#pragma once
#include "core/camera.hpp"
#include "core/chunk.hpp"
#include "utils/constantes.hpp"
#include <glm/glm.hpp>

class Engine {
public:
    Engine(bool wireframe = false, glm::vec3 chunkSize = glm::vec3(64, 16, 64));
    ~Engine();
    
    void update();
    void render();
    void processInput(float dt);
    void renderBlock(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f));
    
    Camera camera;

private:
    const float CHUNK_THRESHOLD;
    
    GLFWwindow* window;
    bool wireframe;
    glm::vec3 chunkSize;  // This is the configurable chunk size
    
    Chunk* currentChunk;
    glm::ivec3 chunkPosition;
    
    void generateChunk();
};