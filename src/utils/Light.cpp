#include "utils/Light.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdio>

Light::Light(glm::vec3 initialPos, int initialMode,
             const char* vertexPath, const char* fragmentPath)
    : lightShader(vertexPath, fragmentPath),
      sphere(initialPos, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(size), 0.0f, 1.0f, 24, 18),
      position(initialPos),
      mode(initialMode) {}

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

void Light::draw(const glm::mat4& view, const glm::mat4& projection) {
    lightShader.use();
    lightShader.setMat4("view", view);
    lightShader.setMat4("projection", projection);

    sphere.position = position;
    sphere.scale = glm::vec3(size);
    sphere.draw(lightShader, glm::mat4(1.0f));
}

void Light::swapMode() {
    mode = (mode == 0) ? 1 : 0;
    printf("Light Mode: %d\n", mode);
}

void Light::move(Movement direction, glm::vec3 front) {
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    if (mode == 1) {
        switch (direction) {
            case Movement::FORWARD:
                front.y = 0.0f;
                position += speed * front;
                break;
            case Movement::BACKWARD:
                front.y = 0.0f;
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
}