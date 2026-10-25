#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "utils/Object.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Tabuleiro : public Object {
public:
    Tabuleiro(glm::vec3 pos = glm::vec3(0.0f), 
              glm::vec3 rot = glm::vec3(0.0f), 
              glm::vec3 scl = glm::vec3(1.0f), 
              float angle = 0.0f);
    
    Tabuleiro(glm::vec3 pos, float angle);

    void init();
    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f)) override;

    // Função utilitária para calcular o centro 3D da casa
    glm::vec3 getPosicaoCasa(int coluna, int linha) const;

    void setPeca(int coluna, int linha, std::unique_ptr<Object> peca);

    bool moverPeca(int origemCol, int origemLin, int destinoCol, int destinoLin);

    Object* getPecaNaCasa(int coluna, int linha) const;
    bool estaOcupada(int coluna, int linha) const;

    float getTamanhoCasa() const { return tamanhoCasa; }
    float getTamanhoCentro() const { return tamanhoCentro; }
    float getAlturaBorda() const { return alturaBorda; }

    bool handleIntersectionLogic(const glm::vec3& rayOriginWorld, const glm::vec3& rayDirWorld, const glm::mat4& sceneModel);

private:
    float tamanhoCentro = 8.0f;
    float espessuraCentro = 0.2f;
    
    float larguraBorda = 0.8f;   
    float alturaBorda = 0.3f;    
    
    float tamanhoCasa = 1.0f; 

    void inicializarPecas();

    std::unique_ptr<Object> grid[8][8];

};

#endif // TABULEIRO_H