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
        glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.6f, 0.5f, 0.2f
    ));

    // 2. MOLDURA DA BASE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.5f, 0.45f, 0.1f
    ));

    // 3. CORPO DA TORRE
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.7f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.45f, 0.45f, 0.8f
    ));

    // 4. CILINDRO DO TOPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.2f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f), 0.0f, 0.55f, 0.55f, 0.2f
    ));

    // 5. MURETINHAS DO TOPO
    int numMuretas = 6;
    float raioBorda = 0.48f;     // Distância do centro até o bordo
    float alturaMureta = 1.35f;  // Posição no topo do cilindro

    for (int i = 0; i < numMuretas; ++i) {
        float anguloPosicao = i * (360.0f / numMuretas); // Passos
        float anguloRad = glm::radians(anguloPosicao);

        float x = raioBorda * cosf(anguloRad);
        float z = raioBorda * sinf(anguloRad);

        // Adiciona 90 graus para alinhar a face tangencialmente
        float anguloRotacaoCubo = -anguloPosicao + 90.0f;

        parts.push_back(std::make_unique<Cube>(
            glm::vec3(x, alturaMureta, z),         // Posição no perímetro
            glm::vec3(0.0f, 1.0f, 0.0f),          // Eixo Y de rotação
            glm::vec3(0.2f, 0.15f, 0.12f),        // Escala (Largura x Altura x Espessura)
            anguloRotacaoCubo                     // Rotação para alinhar a face para fora
        ));
    }
}

void Torre::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) 
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    
    for (auto &part : parts) {
        part->draw(shader, model);
    }
}