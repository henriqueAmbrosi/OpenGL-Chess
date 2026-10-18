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
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.1f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.6f, 0.1f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.45f, 0.1f
    ));


    // 3. PESCOÇO DO CAVALO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.35f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.45f, 0.45f, 0.2f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.55f, 0.0f), glm::vec3(1.00f, 0.0f, 0.0f), glm::vec3(1.0f), 10.0f, 0.4f, 0.3f, 0.4f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.0f, 0.2f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), 30.0f, 0.30f, 0.25f, 0.8f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.35f, 0.40f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.22f, 0.25f, 0.3f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.5f, 0.4f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -25.0f, 0.22f, 0.20f, 0.2f
    ));

    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.65f, 0.3f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -45.0f, 0.175f, 0.25f, 0.5f
    ));
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.75f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -90.0f, 0.25f, 0.25f, 0.5f
    ));


    // 3.1. Crina
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.85f, 0.50f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.7f, 0.3f), 30.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.3f, 0.65f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.45f, 0.3f), 0.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.5f, 0.65f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.2f, 0.3f), 0.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.75f, 0.45f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.7f, 0.3f), -45.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.95f, 0.05f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.5f, 0.3f), -90.0f
    ));
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.9f, -0.2f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.3f, 0.3f), -145.0f
    ));

    // // 4. CABEÇA 
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.45f, -0.445f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), -135.0f, 0.25f, 0.1f, 1.0f
    ));

}
