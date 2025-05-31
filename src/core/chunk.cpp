#include "core/chunk.hpp"
#include "rendering/perlin_noise.hpp"
#include <iostream>
#include <glad/glad.h>

const float Chunk::NOISE_SCALE = 0.05f;

Chunk::Chunk(glm::ivec3 position, int size) 
    : chunkPosition(position), chunkSize(size), blockData(nullptr), 
      VBO(0), VAO(0), EBO(0), texture(0) {
    blockData = new BlockData[chunkSize * chunkSize * chunkSize];
    loadTexture("../assets/texture.jpg");
}

Chunk::~Chunk() {
    delete[] blockData;
    
    // Clean up OpenGL resources
    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);
    if (EBO != 0) glDeleteBuffers(1, &EBO);
    if (texture != 0) glDeleteTextures(1, &texture);
}

void Chunk::generate() {
    int chunkStartX = chunkPosition.x;
    int chunkStartZ = chunkPosition.z;
    
    for (int x = 0; x < chunkSize; x++) {
        for (int z = 0; z < chunkSize; z++) {
            int worldX = chunkStartX + x;
            int worldZ = chunkStartZ + z;
            
            float noiseValue = PerlinNoise::generate(worldX * NOISE_SCALE, worldZ * NOISE_SCALE);
            int terrainHeight = static_cast<int>((noiseValue + 1.0f) * 0.5f * MAX_HEIGHT_OFFSET) + chunkSize / 2;
            
            for (int y = 0; y < chunkSize; y++) {
                int worldY = chunkPosition.y + y;
                int index = getIndex(x, y, z);
                
                if (index < 0 || index >= chunkSize * chunkSize * chunkSize) continue;
                
                if (worldY <= terrainHeight) {
                    blockData[index] = BlockData{ glm::vec3(worldX, worldY, worldZ), BlockType::DIRT };
                } else {
                    blockData[index] = BlockData{ glm::vec3(worldX, worldY, worldZ), BlockType::AIR };
                }
            }
        }
    }
}

BlockData* Chunk::getBlockData() const {
    return blockData;
}

std::vector<float> Chunk::getVisibleFaces(int x, int y, int z) const {
    int index = getIndex(x, y, z);
    if (index < 0 || index >= chunkSize * chunkSize * chunkSize) return {};

    if (blockData[index].type != BlockType::DIRT) return {};

    std::vector<float> visibleFaces;
    Block block; // Contains face definitions

    // RIGHT (+X)
    if (x + 1 >= chunkSize || blockData[getIndex(x + 1, y, z)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.right), std::end(block.right));
    }

    // LEFT (-X)
    if (x - 1 < 0 || blockData[getIndex(x - 1, y, z)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.left), std::end(block.left));
    }

    // TOP (+Y)
    if (y + 1 >= chunkSize || blockData[getIndex(x, y + 1, z)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.top), std::end(block.top));
    }

    // BOTTOM (-Y)
    if (y - 1 < 0 || blockData[getIndex(x, y - 1, z)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.bottom), std::end(block.bottom));
    }

    // FRONT (+Z)
    if (z + 1 >= chunkSize || blockData[getIndex(x, y, z + 1)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.front), std::end(block.front));
    }

    // BACK (-Z)
    if (z - 1 < 0 || blockData[getIndex(x, y, z - 1)].type == BlockType::AIR) {
        visibleFaces.insert(visibleFaces.end(), std::begin(block.back), std::end(block.back));
    }

    return visibleFaces;
}

void Chunk::render() {
    if (mesh.empty()) return;
    
    shader.use();
    shader.setVec3("directionalLight", glm::vec3(-0.5f, -1.0f, -0.3f));

    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh.size() / 8); // Each vertex has 8 components
    glBindVertexArray(0);
}

void Chunk::assembleMesh() {
    mesh.clear(); // Clear existing mesh data
    
    for (int x = 0; x < chunkSize; x++) {
        for (int y = 0; y < chunkSize; y++) {
            for (int z = 0; z < chunkSize; z++) {
                std::vector<float> faces = getVisibleFaces(x, y, z);

                // Apply world offset to vertex positions (x, y, z)
                for (size_t i = 0; i < faces.size(); i += 8) {
                    faces[i + 0] += x + chunkPosition.x; // X position
                    faces[i + 1] += y + chunkPosition.y; // Y position
                    faces[i + 2] += z + chunkPosition.z; // Z position
                }

                mesh.insert(mesh.end(), faces.begin(), faces.end());
            }
        }
    }

    if (mesh.empty()) return;

    // Clean up existing buffers
    if (VBO != 0) glDeleteBuffers(1, &VBO);
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);

    // Turn mesh vector into a C-style array
    float* meshData = mesh.data();
    size_t meshSize = mesh.size() * sizeof(float);

    // Generate VAO & VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, meshSize, meshData, GL_STATIC_DRAW);

    // Vertex layout: [x y z  u v  nx ny nz]
    int stride = 8 * sizeof(float);

    // Position (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // UVs (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normals (location = 2)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO
}

void Chunk::update(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    shader.use(); // Activate shader before setting uniforms
    shader.setMat4("model", modelMatrix);
    shader.setMat4("view", viewMatrix);
    shader.setMat4("projection", projectionMatrix);
}

void Chunk::loadTexture(const char* texturePath) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Load and generate texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 4) format = GL_RGBA;
        else if (nrChannels == 1) format = GL_RED;
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
    
    stbi_image_free(data);
}

glm::ivec3 Chunk::getPosition() const {
    return chunkPosition;
}

int Chunk::getIndex(int x, int y, int z) const {
    return x + chunkSize * (y + chunkSize * z);
}

bool Chunk::isBlockVisible(int x, int y, int z) const {
    int index = getIndex(x, y, z);
    if (index < 0 || index >= chunkSize * chunkSize * chunkSize) return false;
    
    return blockData[index].type != BlockType::AIR;
}