#ifndef OBJECT_H
#define OBJECT_H

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "utils/Shader.h"

class Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    float angle;
    int isSpecial = 0;

    Object();
    Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);

    virtual void draw(Shader& shader, glm::mat4 parentTransform);
    virtual ~Object() {}

    void setCor(const glm::vec3& c) { cor = c; }
    glm::vec3 getCor() const { return cor; }

    void setMaterialID(int id) { materialID = id; }
    int getMaterialID() const { return materialID; }
    void setPosition(glm::vec3 position);

protected:
    glm::vec3 cor = glm::vec3(1.0f);
    int materialID = 2;
    std::vector<std::unique_ptr<Object>> parts;
};

#endif
