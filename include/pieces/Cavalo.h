#pragma once

#include "utils/Object.h"
#include <vector>
#include <memory>

class Cavalo : public Object {
public:
    Cavalo(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle = 0.0f);
    Cavalo(glm::vec3 pos, float angle = 0.0f);

    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f)) override;

private:
    void init();
    std::vector<std::unique_ptr<Object>> parts;
};