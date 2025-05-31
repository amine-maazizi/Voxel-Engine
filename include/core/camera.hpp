#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/constantes.hpp"

class Camera {
    public:
        Camera(
            const glm::vec3& position = glm::vec3(0.0f, 16.0f, 0.0f),
            const glm::vec3& front = glm::vec3(0.0f, 0.0f, -1.0f),
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
            float fov = 45.0f,
            float yaw = -90.0f,
            float pitch = 0.0f,
            float zoom = 45.0f,
            float aspectRatio = WIDTH / HEIGHT,
            float nearPlane = 0.1f,
            float farPlane = 100.0f,
            float cameraSpeed = 2.5f
        );
        ~Camera();

        void update();
        void processInput(float);

        void processMouseMovement(float xPos, float yPos);
        void processMouseScroll(float yoffset);

        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
    public:
        glm::vec3 position;
    private:
        glm::vec3 front;
        glm::vec3 direction;
        glm::vec3 up;
        glm::vec3 worldUp;  
        glm::vec3 right;
        float fov;
        float yaw;
        float pitch;
        float zoom;
        float aspectRatio;
        float nearPlane;
        float farPlane;
        float cameraSpeed;

        bool firstMouse = true; // To avoid jittering on first mouse movement
        float lastX; // Last mouse x position
        float lastY; // Last mouse y position
 };