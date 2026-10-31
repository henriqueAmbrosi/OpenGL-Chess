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
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.23f, 0.09f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.11f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.23f, 0.20f, 0.05f
    ));

    // 3. CORPO DO REI
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.39f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.20f, 0.10f, 0.59f
    ));

    // 4. PRIMEIRO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.70f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.15f, 0.15f, 0.04f
    ));

    // 5. SEGUNDO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.74f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.11f, 0.11f, 0.04f
    ));

    // 6. COROA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.86f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.09f, 0.14f, 0.20f
    ));

    // 7. HASTE VERTICAL DA CRUZ DO REI
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.04f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.05f, 0.16f, 0.05f), 0.0f
    ));

    // 8. HASTE HORIZONTAL DA CRUZ DO REI
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.04f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.16f, 0.05f, 0.05f), 0.0f
    ));
}
