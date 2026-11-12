#include "utils/Camera.h"
#include <cmath>
#include <utils/Movement.h>

Camera::Camera(glm::vec3 startPos, float startYaw, float startPitch)
    : position(startPos), front(glm::vec3(0.0f, 0.0f, -1.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(startYaw), pitch(startPitch) {
    updateCameraVectors();
}

void Camera::move(Movement direction) {
    switch (direction) {
        case Movement::FORWARD:
            position += speed * front;
            break;
        case Movement::BACKWARD:
            position -= speed * front;
            break;
        case Movement::LEFT:
            position -= glm::normalize(glm::cross(front, up)) * speed;
            break;
        case Movement::RIGHT:
            position += glm::normalize(glm::cross(front, up)) * speed;
            break;
        case Movement::UP:
            position += glm::normalize(up) * speed;
            break;
        case Movement::DOWN:
            position -= glm::normalize(up) * speed;
            break;
    }
}

void Camera::rotate(float xOffset, float yOffset) {
    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::applyUniforms(Shader& shader, float aspectRatio) const {
    shader.setMat4("projection", getProjectionMatrix(aspectRatio));
    shader.setMat4("view", getViewMatrix());
    shader.setVec3("viewPos", position);
}

void Camera::updateCameraVectors() {
    glm::vec3 direction;
    direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction.y = std::sin(glm::radians(pitch));
    direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front = glm::normalize(direction);
}