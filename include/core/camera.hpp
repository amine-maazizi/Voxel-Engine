#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Camera {
    public:
        Camera(
            const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
            const glm::vec3& front = glm::vec3(0.0f, 0.0f, -1.0f),
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
            float fov = 45.0f,
            float aspectRatio = 16.0f / 9.0f,
            float nearPlane = 0.1f,
            float farPlane = 100.0f,
            float cameraSpeed = 2.5f
        );
        ~Camera();

        void update();
        void processInput(float);
        void setPosition(const glm::vec3& position);
        void setRotation(const glm::vec3& rotation);
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 direction;
        glm::vec3 up;
        glm::vec3 right;
        float fov;
        float aspectRatio;
        float nearPlane;
        float farPlane;
        float cameraSpeed;
 };