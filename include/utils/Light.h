#pragma once

#include <glm/glm.hpp>
#include <utils/Shader.h>
#include <utils/Movement.h>

class Light {
public:
    glm::vec3 position;
    int mode; // 0 = Spinning, 1 = Free control
    float speed = 0.5f;

    // Parâmetros do modo Spinning
    float radius = 20.0f;
    float height = 12.0f;

    Light(glm::vec3 initialPos = glm::vec3(8.0f, 12.0f, 24.0f), int initialMode = 0);

    void update();

    void applyUniforms(Shader& shader) const;

    void swapMode();

    void move(Movement direction);

    glm::vec3 getPosition() const { return position; }
};