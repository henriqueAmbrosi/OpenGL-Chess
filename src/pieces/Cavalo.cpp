#include "pieces/Cavalo.h"
#include "shapes/TroncoCone.h"
#include "shapes/Cube.h"

Cavalo::Cavalo(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Cavalo::Cavalo(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Cavalo::init() {
    parts.clear();

    // 1 e 2. Base
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. PESCOÇO DO CAVALO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.7f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.45f, 0.3f, 0.8f
    ));

    // 4. CABEÇA 
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.15f, 1.3f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.4f, 0.6f, 0.35f), -25.0f
    ));

    // 5. FOCINHO
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.35f, 1.15f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.3f, 0.3f, 0.3f), -25.0f
    ));
}

void Cavalo::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    for (auto &part : parts) part->draw(shader, model);
}