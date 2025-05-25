#include "core/engine.hpp"

int main() {
    Engine engine;    // Creates engine and OpenGL context
    engine.update();  // Start rendering loop
    return 0;
}