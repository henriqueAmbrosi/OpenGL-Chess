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
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.23f, 0.05f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.23f, 0.27f, 0.05f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.09f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.20f, 0.05f
    ));

    // 3. PESCOÇO DO CAVALO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.16f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.20f, 0.20f, 0.09f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), 10.0f, 0.18f, 0.14f, 0.18f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.45f, 0.09f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), 30.0f, 0.14f, 0.11f, 0.36f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.61f, 0.18f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.10f, 0.11f, 0.14f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.68f, 0.18f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -25.0f, 0.10f, 0.09f, 0.09f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.75f, 0.14f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -45.0f, 0.08f, 0.11f, 0.23f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.80f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -90.0f, 0.11f, 0.11f, 0.23f
    ));

    // 3.1. Crina
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.39f, 0.23f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.32f, 0.14f), 30.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.59f, 0.30f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.20f, 0.14f), 0.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.68f, 0.30f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.09f, 0.14f), 0.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.80f, 0.20f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.32f, 0.14f), -45.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.89f, 0.02f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.23f, 0.14f), -90.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.86f, -0.09f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.02f, 0.14f, 0.14f), -145.0f
    ));

    // 4. CABEÇA 
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.66f, -0.20f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -135.0f, 0.11f, 0.05f, 0.45f
    ));
}