#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "utils/Object.h"
#include "utils/Shader.h"

class TroncoCone : public Object {
public:
    TroncoCone(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), float angle = 0.0f, float radiusBottom = 0.5f, float radiusTop = 0.3f, float height = 1.0f, unsigned int sectors = 36);
    ~TroncoCone();

    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f)) override;

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;
    void init(float radiusBottom, float radiusTop, float height, unsigned int sectors);
};