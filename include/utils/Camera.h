#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Shader.h>
#include <utils/Movement.h>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float yaw;
    float pitch;
    float speed = 0.15f;
    float sensitivity = 1.0f;
    float fov = 45.0f;

    Camera(glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 0.0f),
           float startYaw = -90.0f,
           float startPitch = 0.0f);

    void move(Movement direction);
    void rotate(float xOffset, float yOffset);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio) const;

    void applyUniforms(Shader& shader, float aspectRatio) const;

private:
    void updateCameraVectors();
};