# Voxel-Engine
A Voxel Engine written in C++ and OpenGL

## Folder Structure
The final project will be organized as follows to keep code modular and maintainable:

```
Voxel-Engine/
├── include/                    # Header files for classes and utilities
│   ├── core/                  # Core engine components
│   │   ├── Block.hpp          # Block data structure
│   │   ├── Chunk.hpp          # Chunk data and rendering
│   │   ├── World.hpp          # World management (chunks, player)
│   │   └── Camera.hpp         # Camera for view/projection
│   ├── rendering/             # Rendering-related components
│   │   ├── Shader.hpp         # Shader management
│   │   ├── Mesh.hpp           # Mesh data (vertices, indices)
│   │   └── Renderer.hpp       # OpenGL rendering logic
│   └── utils/                 # Utility functions and libraries
│       ├── Noise.hpp          # Noise generation for terrain
│       └── Math.hpp           # Math helpers (vectors, matrices)
├── src/                       # Source files
│   ├── core/                  # Implementation of core components
│   │   ├── Block.cpp
│   │   ├── Chunk.cpp
│   │   ├── World.cpp
│   │   └── Camera.cpp
│   ├── rendering/             # Implementation of rendering components
│   │   ├── Shader.cpp
│   │   ├── Mesh.cpp
│   │   └── Renderer.cpp
│   └── utils/                 # Implementation of utilities
│       ├── Noise.cpp
│       └── Math.cpp
├── shaders/                   # GLSL shader files
│   ├── basic.vert             # Vertex shader for colored blocks
│   └── basic.frag             # Fragment shader for colored blocks
├── lib/                       # External libraries
│   ├── glfw/                  # GLFW for window/input handling
│   ├── glad/                  # GLAD for OpenGL function loading
│   └── glm/                   # GLM for matrix/vector math
├── assets/                    # Placeholder for future textures or data
├── build/                     # Build output (binaries, objects)
├── CMakeLists.txt             # CMake build configuration
└── README.md                  # Project documentation
```

## Dependencies

- **GLFW**: Window and input handling.
- **GLAD**: OpenGL function loading.
- **GLM**: Matrix and vector math.
- **FastNoiseLite**: Procedural terrain generation.

## Build Instructions

1. Install dependencies (GLFW, GLAD, GLM).
2. Configure with CMake.
3. Build and run from `build/`.
