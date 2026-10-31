#include "pieces/Rainha.h"
#include "shapes/TroncoCone.h"
#include "shapes/Esfera.h"
#include "shapes/Cube.h"
#include <cmath>

Rainha::Rainha(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Rainha::Rainha(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Rainha::init() {
    parts.clear();

    // 1. BASE INFERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.23f, 0.09f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.11f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.23f, 0.20f, 0.05f
    ));

    // 3. CORPO DA RAINHA
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
        glm::vec3(0.0f, 0.86f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.10f, 0.17f, 0.20f
    ));

    // 7. PONTAS DA COROA
    int numPontas = 8;
    float raioBorda = 0.18f;
    float alturaPontas = 0.97f;

    for (int i = 0; i < numPontas; ++i) {
        float anguloGraus = i * (360.0f / numPontas);
        float anguloRad = glm::radians(anguloGraus);

        float x = raioBorda * cosf(anguloRad);
        float z = raioBorda * sinf(anguloRad);

        parts.push_back(std::make_unique<Esfera>(
            glm::vec3(x, alturaPontas, z),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.06f),
            0.0f, 0.5f
        ));
    }

    // 8. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 0.97f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.16f, 0.15f, 0.16f), 0.0f, 0.7f
    ));

    // 9. ORNAMENTO DO TOPO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.08f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.06f), 0.0f, 0.5f
    ));
}
