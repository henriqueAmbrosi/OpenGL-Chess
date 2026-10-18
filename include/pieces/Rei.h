#pragma once

#include "utils/Object.h"
#include <vector>
#include <memory>

class Rei : public Object {
public:
    Rei(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle = 0.0f);
    Rei(glm::vec3 pos, float angle = 0.0f);

private:
    void init();
};