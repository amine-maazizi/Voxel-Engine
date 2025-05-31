cmake_minimum_required(VERSION 3.10)
project(VoxelEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Paths to your local libs - adjust if needed
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/lib/glad)
set(GLM_DIR  ${CMAKE_SOURCE_DIR}/lib/glm)

# Include directories
include_directories(
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${GLM_DIR}
    ${CMAKE_SOURCE_DIR}/lib/stb_image
    ${CMAKE_SOURCE_DIR}/include
)

# GLAD source file
set(GLAD_SRC ${GLAD_DIR}/src/glad.c)

# Source files
set(SOURCES
    src/main.cpp
    
    src/rendering/shader.cpp
    src/rendering/perlin_noise.cpp

    src/core/engine.cpp
    src/core/block.cpp
    src/core/camera.cpp
    src/core/chunk.cpp

    src/utils/stb_image.cpp

    ${GLAD_SRC}
)

# Create executable
add_executable(VoxelEngine ${SOURCES})

# Link libraries - GLFW built for MinGW assumed here
target_link_libraries(VoxelEngine
    ${GLFW_DIR}/lib-mingw-w64/libglfw3.a    # Correct path to GLFW static lib
    -lopengl32                              # Windows OpenGL library
    -lgdi32                                # Windows GDI library
    -luser32                               # Windows User library
    -lkernel32                             # Windows Kernel library
)

#  Define GLFW_STATIC if linking statically
target_compile_definitions(VoxelEngine PRIVATE GLFW_STATIC)
