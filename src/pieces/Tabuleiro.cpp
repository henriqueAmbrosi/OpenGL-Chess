#include "pieces/Tabuleiro.h"
#include "shapes/Cube.h"

Tabuleiro::Tabuleiro(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Tabuleiro::Tabuleiro(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Tabuleiro::init() {
    parts.clear();

    tamanhoCasa = tamanhoCentro / 8.0f;

    // 1. CUBO CENTRAL
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, espessuraCentro / 2.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(tamanhoCentro, espessuraCentro, tamanhoCentro),
        0.0f
    ));

    // 2. MOLDURAS DA BORDA
    float deslocamentoCentro = (tamanhoCentro / 2.0f) + (larguraBorda / 2.0f);
    float comprimentoBordaComQuinas = tamanhoCentro + (2.0f * larguraBorda);
    float yPosBorda = alturaBorda / 2.0f;

    // Borda Norte
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, yPosBorda, deslocamentoCentro),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(comprimentoBordaComQuinas, alturaBorda, larguraBorda),
        0.0f
    ));

    // Borda Sul
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(0.0f, yPosBorda, -deslocamentoCentro),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(comprimentoBordaComQuinas, alturaBorda, larguraBorda),
        0.0f
    ));

    // Borda Leste
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(deslocamentoCentro, yPosBorda, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(larguraBorda, alturaBorda, tamanhoCentro),
        0.0f
    ));

    // Borda Oeste
    parts.push_back(std::make_unique<Cube>(
        glm::vec3(-deslocamentoCentro, yPosBorda, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(larguraBorda, alturaBorda, tamanhoCentro),
        0.0f
    ));
}

void Tabuleiro::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) 
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    
    if (parts.empty()) return;

    // 1. Desenha o CUBO CENTRAL
    shader.setInt("materialID", 0);
    parts[0]->draw(shader, model);

    // 2. Desenha as BORDAS
    shader.setInt("materialID", 1);
    for (size_t i = 1; i < parts.size(); ++i) {
        parts[i]->draw(shader, model);
    }
}