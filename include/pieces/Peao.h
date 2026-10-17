#ifndef PEAO_H
#define PEAO_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/Object.h"
#include "utils/Shader.h"
#include <vector>
#include <memory>


class Peao : public Object{
public:

    Peao(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Peao(glm::vec3 pos, float ang);

    void init();
    void draw(Shader &shader, glm::mat4 model);

private:

    std::vector<std::unique_ptr<Object>> parts;

};

#endif
