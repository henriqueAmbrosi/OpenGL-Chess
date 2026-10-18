#pragma once

#include "utils/Object.h"
#include <vector>
#include <memory>

class Bispo : public Object {
public:
    Bispo(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle = 0.0f);
    Bispo(glm::vec3 pos, float angle = 0.0f);

private:
    void init();
};