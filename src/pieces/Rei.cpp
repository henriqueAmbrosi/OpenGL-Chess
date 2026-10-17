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

    // 1. BASE INFERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO DO REI
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.85f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.45f, 0.22f, 1.3f
    ));

    // 4. PRIMEIRO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.54f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.32f, 0.32f, 0.08f
    ));

    // 5. SEGUNDO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.63f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.25f, 0.25f, 0.08f
    ));

    // 6. COROA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.90f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.20f, 0.30f, 0.44f
    ));

    // 7. HASTE VERTICAL DA CRUZ DO REI
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.33f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), 0.0f
    ));

    // 8. HASTE HORIZONTAL DA CRUZ DO REI
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.34f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.35f, 0.1f, 0.1f), 0.0f
    ));
}

void Rei::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) 
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    
    for (auto &part : parts) {
        part->draw(shader, model);
    }
}