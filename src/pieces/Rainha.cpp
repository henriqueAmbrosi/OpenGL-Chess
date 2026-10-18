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
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO DA RAINHA
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
        glm::vec3(0.0f, 1.90f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.22f, 0.38f, 0.44f
    ));

    // 7. PONTAS DA COROA
    int numPontas = 8;
    float raioBorda = 0.39f;
    float alturaPontas = 2.13f;

    for (int i = 0; i < numPontas; ++i) {
        float anguloGraus = i * (360.0f / numPontas);
        float anguloRad = glm::radians(anguloGraus);

        float x = raioBorda * cosf(anguloRad);
        float z = raioBorda * sinf(anguloRad);

        parts.push_back(std::make_unique<Esfera>(
            glm::vec3(x, alturaPontas, z),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.14f, 0.14f, 0.14f), // Esferas maiores (de 0.08f para 0.14f)
            0.0f, 0.5f
        ));
    }

    // 8. CABEÇA
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 2.13f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.35f, 0.32f, 0.35f), 0.0f, 0.7f
    ));

    // 9. ORNAMENTO DO TOPO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 2.38f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.13f, 0.13f, 0.13f), 0.0f, 0.5f
    ));
}
