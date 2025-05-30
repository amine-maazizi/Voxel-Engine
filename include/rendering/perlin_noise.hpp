#pragma once
#include <glm/glm.hpp>
#include <glm/glm.hpp>

class PerlinNoise {
public:
    // Sample Perlin noise at coordinates x, y, scaled to chunkSize
    static float generate(float x, float y);

private:
    // Generate a random gradient vector at integer coordinates
    static glm::vec2 randomGradient(int ix, int iy);
    
    // Computes the dot product of the distance and gradient vectors
    static float dotGridGradient(int ix, int iy, float x, float y);
    
    // Interpolate between two values
    static float interpolate(float a0, float a1, float w);
};