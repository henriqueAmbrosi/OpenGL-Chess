#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils/Object.h"
#include "utils/Shader.h"

class Esfera : public Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;

    Esfera(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float angle = 0.0f, float radius = 0.5f, unsigned int sectors = 36, unsigned int stacks = 18);
    ~Esfera();

    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f));

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;
    void init(float radius, unsigned int sectors, unsigned int stacks);
};