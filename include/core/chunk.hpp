#pragma once
#include <glm/glm.hpp>
#include "core/block.hpp"

class Chunk {
public:
    Chunk(glm::ivec3 position, int size);
    ~Chunk();
    
    void generate();
    BlockData* getBlockData() const;
    bool isBlockVisible(int x, int y, int z) const;
    glm::ivec3 getPosition() const;
    
private:
    static const int CHUNK_SIZE = 16;
    static const float NOISE_SCALE;
    static const int MAX_HEIGHT_OFFSET = 8;
    
    glm::ivec3 chunkPosition;
    int chunkSize;
    BlockData* blockData;
    
    int getIndex(int x, int y, int z) const;
};