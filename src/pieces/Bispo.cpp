#include "pieces/Bispo.h"
#include "shapes/TroncoCone.h"
#include "shapes/Esfera.h"

Bispo::Bispo(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Bispo::Bispo(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Bispo::init() {
    parts.clear();

    // 1 e 2. Base
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO DO BISPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.75f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.42f, 0.2f, 0.9f
    ));

    // 4. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.4f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.6f, 0.9f, 0.6f), 0.0f, 0.5f
    ));
}

void Bispo::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    for (auto &part : parts) part->draw(shader, model);
}