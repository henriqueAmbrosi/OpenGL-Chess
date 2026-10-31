#include "pieces/Bispo.h"
#include "shapes/TroncoCone.h"
#include "shapes/Esfera.h"

Bispo::Bispo(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Bispo::Bispo(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Bispo::init() {
    parts.clear();

    // 1. BASE INFERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.23f, 0.09f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.11f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.23f, 0.20f, 0.05f
    ));

    // 3. CORPO DO BISPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.32f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.19f, 0.10f, 0.36f
    ));

    // 4. PRIMEIRO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.52f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.13f, 0.13f, 0.03f
    ));

    // 5. SEGUNDO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.56f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.11f, 0.11f, 0.03f
    ));

    // 6. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 0.70f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.25f, 0.34f, 0.25f), 0.0f, 0.5f
    ));

    // 7. ORNAMENTO DO TOPO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 0.89f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.08f), 0.0f, 0.5f
    ));
}