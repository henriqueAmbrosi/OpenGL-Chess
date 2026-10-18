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
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO DO BISPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.7f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.42f, 0.22f, 0.8f
    ));

    // 4. PRIMEIRO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.15f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.28f, 0.28f, 0.07f
    ));

    // 5. SEGUNDO ANEL DA GOLA
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.23f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.25f, 0.25f, 0.07f
    ));

    // 6. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.55f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.55f, 0.75f, 0.55f), 0.0f, 0.5f
    ));

    // 7. ORNAMENTO DO TOPO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.95f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.18f, 0.18f, 0.18f), 0.0f, 0.5f
    ));
}