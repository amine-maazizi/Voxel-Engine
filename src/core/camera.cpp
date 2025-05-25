#include "core/camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

// Constructor with all parameters
Camera::Camera(
    const glm::vec3& position,
    const glm::vec3& front,
    const glm::vec3& up,
    float fov,
    float yaw,
    float pitch,
    float zoom,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    float cameraSpeed
) :
    position(position),
    front(front),
    up(up),
    worldUp(up),  
    fov(fov),
    yaw(yaw),
    pitch(pitch),
    zoom(zoom),
    aspectRatio(aspectRatio),
    nearPlane(nearPlane),
    farPlane(farPlane),
    cameraSpeed(cameraSpeed),

    firstMouse(true),
    lastX(0.0f), 
    lastY(0.0f)  
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

void Camera::processMouseMovement(float xPos, float yPos)
{
    if (firstMouse) {
        lastX = xPos; // Initialize last mouse positions
        lastY = yPos;
        firstMouse = false; // Reset first mouse flag
    }

    // Calculate the change in mouse position
    float xoffset = xPos - lastX;
    float yoffset = lastY - yPos; // Invert y-axis for correct camera movement

    lastX = xPos; // Update last mouse positions
    lastY = yPos;

    // Sensitivity factor
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // Update yaw and pitch based on mouse movement
    yaw += xoffset;
    pitch += yoffset;

    // Constrain pitch to avoid gimbal lock
    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    update(); // Update camera vectors based on new yaw and pitch

}

void Camera::processMouseScroll(float yoffset)
{
    // Adjust the field of view based on mouse scroll
    fov -= yoffset;
    if (fov < 1.0f) {
        fov = 1.0f; // Prevent zooming in too much
    } else if (fov > 45.0f) {
        fov = 45.0f; // Prevent zooming out too much
    }
}


// Update the camera's direction, right, and up vectors based on position and target
void Camera::update()
{
    // Update the front vector based on yaw and pitch
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    // Update the right vector
    right = glm::normalize(glm::cross(front, worldUp));

    // Update the up vector
    up = glm::normalize(glm::cross(right, front));
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
    yaw = rotation.y; // Yaw is around the Y-axis
    pitch = rotation.x; // Pitch is around the X-axis
    update(); // Update the camera vectors based on new yaw and pitch   
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
