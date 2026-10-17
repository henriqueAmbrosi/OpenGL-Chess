#include "pieces/Rei.h"
#include "shapes/TroncoCone.h"
#include "shapes/Esfera.h"
#include "shapes/Cube.h"

Rei::Rei(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Rei::Rei(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Rei::init() {
    parts.clear();

    // 1 e 2. Base
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.85f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.48f, 0.3f, 1.1f
    ));

    // 4. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.6f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.75f, 0.75f, 0.75f), 0.0f, 0.5f
    ));

    // 5. CRUZ DO REI
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.3f, 0.1f), 0.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.3f, 0.1f, 0.1f), 0.0f
    ));
}

void Rei::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    for (auto &part : parts) part->draw(shader, model);
}