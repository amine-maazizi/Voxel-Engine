#include "core/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Constructor with all parameters
Camera::Camera(
    const glm::vec3& position,
    const glm::vec3& front,
    const glm::vec3& up,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    float cameraSpeed
) :
    position(position),
    front(front),
    up(up),
    fov(fov),
    aspectRatio(aspectRatio),
    nearPlane(nearPlane),
    farPlane(farPlane),
    cameraSpeed(cameraSpeed) // Default camera speed
{
    update();
}

// Destructor
Camera::~Camera() {}

// Process input for camera movement (placeholder, can be expanded)
void Camera::processInput(float dt)
{
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        position += front * cameraSpeed * dt; // Move forward
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        position -= front * cameraSpeed * dt; // Move backward
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::normalize(glm::cross(front, up)) * cameraSpeed * dt; // Move left
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::normalize(glm::cross(front, up)) * cameraSpeed * dt; // Move right
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
        position += up * cameraSpeed * dt; // Move up
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= up * cameraSpeed * dt; // Move down
    }
}

// Update the camera's direction, right, and up vectors based on position and target
void Camera::update()
{

}

// Set camera position and update vectors
void Camera::setPosition(const glm::vec3& newPosition)
{
    position = newPosition;
    update();
}

// Set camera rotation (we interpret rotation as changing target relative to position)
void Camera::setRotation(const glm::vec3& rotation)
{
    
}

// Return the view matrix (using glm::lookAt)
glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

// Return the projection matrix (perspective)
glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}
