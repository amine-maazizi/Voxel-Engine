#include "core/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Constructor with all parameters
Camera::Camera(
    const glm::vec3& position,
    const glm::vec3& target,
    const glm::vec3& up,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    float cameraSpeed
) :
    position(position),
    target(target),
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
    // This function can be expanded to handle keyboard input
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        position -= direction * cameraSpeed * dt;
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        position += direction * cameraSpeed * dt;
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        position += right * cameraSpeed * dt;
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        position -= right * cameraSpeed * dt;
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
        position += up * cameraSpeed * dt; // Move up
    } else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= up * cameraSpeed * dt; // Move down
    }
}

// Update the camera's direction, right, and up vectors based on position and target
void Camera::update()
{
    // std::cout << "{" << position.x << ", " << position.y << ", " << position.z << "}" << std::endl;
    // Direction vector points from position to target
    direction = glm::normalize(target - position);

    // Right vector is perpendicular to the direction and world up vector
    right = glm::normalize(glm::cross(direction, up));

    // Recalculate the camera's up vector (orthogonal to direction and right)
    this->up = glm::cross(right, direction);
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
    // This is a simple placeholder to convert rotation Euler angles to a new target
    // In practice, you would use proper rotation math here
    glm::mat4 rotationMat(1.0f);
    rotationMat = glm::rotate(rotationMat, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rotationMat = glm::rotate(rotationMat, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rotationMat = glm::rotate(rotationMat, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    glm::vec4 dir = rotationMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);  // Default looking down -Z

    target = position + glm::vec3(dir);
    update();
}

// Return the view matrix (using glm::lookAt)
glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, target, up);
}

// Return the projection matrix (perspective)
glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}
