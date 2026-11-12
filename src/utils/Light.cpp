#include "utils/Light.h"
#include <GLFW/glfw3.h>
#include <cmath>

Light::Light(glm::vec3 initialPos, int initialMode)
    : position(initialPos), mode(initialMode) {}

void Light::update() {
    if (mode == 0) {
        float tempo = static_cast<float>(glfwGetTime());
        float distancia = speed * tempo;
        position = glm::vec3(
            std::sin(distancia) * radius,
            height,
            std::cos(distancia) * radius
        );
    }
}

void Light::applyUniforms(Shader& shader) const {
    shader.setVec3("lightPos", position);
}

void Light::swapMode() {
    if(mode == 0) mode = 1;
    else mode = 0;
    printf("Light Mode: %d", mode);
}

void Light::move(Movement direction) {
    if(mode == 1){
        switch (direction) {
            case Movement::FORWARD:
                position += glm::vec3(0.0f, 0.0f, 1.0f) * speed;
                break;
            case Movement::BACKWARD:
                position -= glm::vec3(0.0f, 0.0f, 1.0f) * speed;
                break;
            case Movement::LEFT:
                position -= glm::vec3(1.0f, 0.0f, 0.0f) * speed;
                break;
            case Movement::RIGHT:
                position += glm::vec3(1.0f, 0.0f, 0.0f) * speed;
                break;
            case Movement::UP:
                position += glm::vec3(0.0f, 1.0f, 0.0f) * speed;
                break;
            case Movement::DOWN:
                position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed;
                break;
        }
    }
}