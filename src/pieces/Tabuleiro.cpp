#include "pieces/Tabuleiro.h"
#include "shapes/Cube.h"
#include <cstddef>
#include <glm/ext/vector_float3.hpp>
#include <pieces/Peao.h>
#include <pieces/Cavalo.h>
#include <pieces/Torre.h>
#include <pieces/Bispo.h>
#include <pieces/Rei.h>
#include <pieces/Rainha.h>

Tabuleiro::Tabuleiro(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle) { init(); }

Tabuleiro::Tabuleiro(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), angle) { init(); }

void Tabuleiro::inicializarPecas(){
    float escalaPeca = 0.75f; 
    glm::vec3 corBranca = glm::vec3(0.9f, 0.9f, 0.85f);
    glm::vec3 corPreta  = glm::vec3(0.2f, 0.15f, 0.1f);

    auto setupBranca = [&](std::unique_ptr<Object>& slot, auto* pecaCriada) {
        slot.reset(pecaCriada);
        slot->scale = glm::vec3(escalaPeca);
        slot->setCor(corBranca);
        slot->setMaterialID(2);
    };

    auto setupPreta = [&](std::unique_ptr<Object>& slot, auto* pecaCriada) {
        slot.reset(pecaCriada);
        slot->scale = glm::vec3(escalaPeca);
        slot->setCor(corPreta);
        slot->setMaterialID(2);
    };

    // --- PEÇAS BRANCAS ---
    setupBranca(grid[0][0], new Torre(getPosicaoCasa(0, 0), 0.0f));
    setupBranca(grid[1][0], new Cavalo(getPosicaoCasa(1, 0), 0.0f));
    setupBranca(grid[2][0], new Bispo(getPosicaoCasa(2, 0), 0.0f));
    setupBranca(grid[3][0], new Rainha(getPosicaoCasa(3, 0), 0.0f));
    setupBranca(grid[4][0], new Rei(getPosicaoCasa(4, 0), 0.0f));
    setupBranca(grid[5][0], new Bispo(getPosicaoCasa(5, 0), 0.0f));
    setupBranca(grid[6][0], new Cavalo(getPosicaoCasa(6, 0), 0.0f));
    setupBranca(grid[7][0], new Torre(getPosicaoCasa(7, 0), 0.0f));

    for (int i = 0; i < 8; ++i) {
        setupBranca(grid[i][1], new Peao(getPosicaoCasa(i, 1), 0.0f));
    }

    // --- PEÇAS PRETAS ---
    for (int i = 0; i < 8; ++i) {
        setupPreta(grid[i][6], new Peao(getPosicaoCasa(i, 6), 0.0f));
    }

    setupPreta(grid[0][7], new Torre(getPosicaoCasa(0, 7), 0.0f));
    setupPreta(grid[1][7], new Cavalo(getPosicaoCasa(1, 7), 0.0f));
    setupPreta(grid[2][7], new Bispo(getPosicaoCasa(2, 7), 0.0f));
    setupPreta(grid[3][7], new Rainha(getPosicaoCasa(3, 7), 0.0f));
    setupPreta(grid[4][7], new Rei(getPosicaoCasa(4, 7), 0.0f));
    setupPreta(grid[5][7], new Bispo(getPosicaoCasa(5, 7), 0.0f));
    setupPreta(grid[6][7], new Cavalo(getPosicaoCasa(6, 7), 0.0f));
    setupPreta(grid[7][7], new Torre(getPosicaoCasa(7, 7), 0.0f));

    Object* cavaloBranco = grid[1][0].get();
    cavaloBranco->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    cavaloBranco->angle = 180.0f;

    cavaloBranco = grid[6][0].get();
    cavaloBranco->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    cavaloBranco->angle = 180.0f;
}

void Tabuleiro::selectPiece(const glm::vec3& rayOriginWorld, const glm::vec3& rayDirWorld, const glm::mat4& model) {
    glm::mat4 inv = glm::inverse(model);
    auto ro = glm::vec3(inv * glm::vec4(rayOriginWorld, 1));
    auto rd = normalize(glm::vec3(inv * glm::vec4(rayDirWorld, 0)));

    float t;
    if (std::abs(rd.y) < 1e-6f) return;
    t = (espessuraCentro - ro.y) / rd.y;
    if (t < 0) return;
    glm::vec3 hit = ro + rd * t;

    float offset = -3.5f * tamanhoCasa;
    selectedCol = (int)glm::round((hit.x - offset) / tamanhoCasa);
    selectedLine = (int)glm::round((hit.z - offset) / tamanhoCasa);
    if (selectedCol < 0 || selectedCol > 7 || selectedLine < 0 || selectedLine > 7) return;

    selectedPiece = getPecaNaCasa(selectedCol, selectedLine);
    if (selectedPiece != nullptr) {
        selectedPiece->isSpecial = 1;
    }
}

void Tabuleiro::movePiece(const glm::vec3& rayOriginWorld, const glm::vec3& rayDirWorld, const glm::mat4& model) {
    if (selectedPiece == nullptr) return;

    glm::mat4 inv = glm::inverse(model);
    auto ro = glm::vec3(inv * glm::vec4(rayOriginWorld, 1));
    auto rd = normalize(glm::vec3(inv * glm::vec4(rayDirWorld, 0)));

    float t;
    if (std::abs(rd.y) < 1e-6f) return;
    t = (espessuraCentro - ro.y) / rd.y;
    if (t < 0) return;
    glm::vec3 hit = ro + rd * t;

    float offset = -3.5f * tamanhoCasa;
    int col = (int)glm::round((hit.x - offset) / tamanhoCasa);
    int lin = (int)glm::round((hit.z - offset) / tamanhoCasa);
    if (col < 0 || col > 7 || lin < 0 || lin > 7) return;

    printf("moving to col: %d line: %d\n", col, lin);
    
    if (moverPeca(selectedCol, selectedLine, col, lin)) {
        if (selectedPiece != nullptr) {
            selectedPiece->isSpecial = 0;
        }
    }
    selectedPiece = nullptr;
}

void Tabuleiro::init() {
    parts.clear();

    tamanhoCasa = tamanhoCentro / 8.0f;

    for (int col = 0; col < 8; ++col) {
        for (int lin = 0; lin < 8; ++lin) {
            grid[col][lin] = nullptr;
        }
    }

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

    inicializarPecas();
}

// Retorna as coordenadas locais da casa no tabuleiro
glm::vec3 Tabuleiro::getPosicaoCasa(int coluna, int linha) const {
    float offsetInicio = -3.5f * tamanhoCasa;
    float localX = offsetInicio + (coluna * tamanhoCasa);
    float localZ = offsetInicio + (linha * tamanhoCasa);
    float localY = espessuraCentro;

    return glm::vec3(localX, localY, localZ);
}

void Tabuleiro::setPeca(int coluna, int linha, std::unique_ptr<Object> peca) {
    if (coluna >= 0 && coluna < 8 && linha >= 0 && linha < 8) {
        grid[coluna][linha] = std::move(peca);
    }
}

bool Tabuleiro::moverPeca(int origemCol, int origemLin, int destinoCol, int destinoLin) {
    if (origemCol < 0 || origemCol >= 8 || origemLin < 0 || origemLin >= 8 ||
        destinoCol < 0 || destinoCol >= 8 || destinoLin < 0 || destinoLin >= 8) {
        return false;
    }

    if (grid[origemCol][origemLin] == nullptr) {
        return false;
    }

    if (origemCol == destinoCol && origemLin == destinoLin) {
        return true;
    }

    (*grid[origemCol][origemLin]).setPosition(getPosicaoCasa(destinoCol, destinoLin));
    grid[destinoCol][destinoLin] = std::move(grid[origemCol][origemLin]);
    grid[origemCol][origemLin] = nullptr;
    return true;
}

Object* Tabuleiro::getPecaNaCasa(int coluna, int linha) const {
    if (coluna >= 0 && coluna < 8 && linha >= 0 && linha < 8) {
        return grid[coluna][linha].get();
    }
    return nullptr;
}

bool Tabuleiro::hasSelectedPiece() {
    return selectedPiece != nullptr;
}

bool Tabuleiro::estaOcupada(int coluna, int linha) const {
    return getPecaNaCasa(coluna, linha) != nullptr;
}

void Tabuleiro::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);
    if (glm::length(rotation) > 0.0f) 
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));
    model = glm::scale(model, scale);
    
    if (parts.empty()) return;

    // 1. Desenha o CUBO CENTRAL (Tabuleiro)
    shader.setInt("materialID", 0);
    parts[0]->draw(shader, model);

    // 2. Desenha as BORDAS (Tabuleiro)
    shader.setInt("materialID", 1);
    for (size_t i = 1; i < parts.size(); ++i) {
        parts[i]->draw(shader, model);
    }

    // 3. Desenha as PEÇAS
    for (int col = 0; col < 8; ++col) {
        for (int lin = 0; lin < 8; ++lin) {
            Object* peca = grid[col][lin].get();
            if (peca != nullptr) {
                peca->draw(shader, model);
            }
        }
    }
}