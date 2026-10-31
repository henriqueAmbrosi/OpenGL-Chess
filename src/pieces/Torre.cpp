#include "pieces/Torre.h"
#include "shapes/TroncoCone.h"
#include "shapes/Cube.h"
#include <cmath>

Torre::Torre(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Torre::Torre(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Torre::init() {
    parts.clear();

    // 1. BASE INFERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.27f, 0.23f, 0.09f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.11f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.23f, 0.20f, 0.05f
    ));

    // 3. CORPO DA TORRE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.32f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.20f, 0.20f, 0.36f
    ));

    // 4. CILINDRO DO TOPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.55f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.25f, 0.25f, 0.09f
    ));

    // 5. MURETINHAS DO TOPO
    int numMuretas = 6;
    float raioBorda = 0.22f;
    float alturaMureta = 0.61f;

    for (int i = 0; i < numMuretas; ++i) {
        float anguloPosicao = i * (360.0f / numMuretas);
        float anguloRad = glm::radians(anguloPosicao);

        float x = raioBorda * cosf(anguloRad);
        float z = raioBorda * sinf(anguloRad);
        float anguloRotacaoCubo = -anguloPosicao + 90.0f;

        parts.push_back(std::make_unique<Cube>(
            glm::vec3(x, alturaMureta, z),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.09f, 0.07f, 0.05f),
            anguloRotacaoCubo
        ));
    }
}