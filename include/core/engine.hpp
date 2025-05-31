#pragma once
#include "core/camera.hpp"
#include "core/chunk.hpp"
#include "utils/constantes.hpp"

class Engine {
public:
    Engine(bool wireframe = true, int chunkSize = 16);
    ~Engine();
    
    void update();
    void render();
    void processInput(float dt);
    void renderBlock(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f));
    
    Camera camera;

private:
    const int CHUNK_SIZE;
    const float CHUNK_THRESHOLD;
    
    GLFWwindow* window;
    bool wireframe;
    int chunkSize;
    
    Chunk* currentChunk;
    glm::ivec3 chunkPosition;
    
    void generateChunk();
};