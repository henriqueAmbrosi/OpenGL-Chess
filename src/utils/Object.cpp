#include "utils/Object.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>  // se usar glm::rotate, glm::translate etc.
#include <glm/gtc/type_ptr.hpp>

Object::Object()
    : position(0.0f), rotation(1.0f, 0.0f, 0.0f), scale(1.0f), angle(0.0f)
{}

Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : position(pos), rotation(rot), scale(scl), angle(angle)
{
    // construtor básico — inicializa os valores recebidos
}

void Object::setPosition(glm::vec3 pos) {
    position = pos;
}

void Object::draw(Shader &shader, glm::mat4 parentModel) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(parentModel, position);
    if (glm::length(rotation) > 0.0f) {
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    }
    model = glm::scale(model, scale);

    shader.setInt("materialID", materialID);
    shader.setVec3("objectColor", cor);

    for (auto& part : parts) {
        part->draw(shader, model);
    }

}
