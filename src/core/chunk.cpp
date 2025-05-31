#include "core/chunk.hpp"
#include "rendering/perlin_noise.hpp"
#include <iostream>

const float Chunk::NOISE_SCALE = 0.05f;

Chunk::Chunk(glm::ivec3 position, int size) 
    : chunkPosition(position), chunkSize(size), blockData(nullptr) {
    blockData = new BlockData[chunkSize * chunkSize * chunkSize];
}

Chunk::~Chunk() {
    delete[] blockData;
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

bool Chunk::isBlockVisible(int x, int y, int z) const {
    int index = getIndex(x, y, z);
    if (index < 0 || index >= chunkSize * chunkSize * chunkSize) return false;
    if (blockData[index].type != BlockType::DIRT) return false;
    
    for (auto [dx, dy, dz] : std::vector<std::tuple<int, int, int>>{
        {1, 0, 0}, {-1, 0, 0},
        {0, 1, 0}, {0, -1, 0},
        {0, 0, 1}, {0, 0, -1}}) {
        
        int nx = x + dx;
        int ny = y + dy;
        int nz = z + dz;
        
        if (nx < 0 || ny < 0 || nz < 0 || nx >= chunkSize || ny >= chunkSize || nz >= chunkSize) {
            return true;
        }
        
        int nIndex = getIndex(nx, ny, nz);
        if (nIndex >= 0 && nIndex < chunkSize * chunkSize * chunkSize &&
            blockData[nIndex].type == BlockType::AIR) {
            return true;
        }
    }
    
    return false;
}

glm::ivec3 Chunk::getPosition() const {
    return chunkPosition;
}

int Chunk::getIndex(int x, int y, int z) const {
    return x + chunkSize * (y + chunkSize * z);
}