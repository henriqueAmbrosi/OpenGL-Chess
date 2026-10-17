#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "utils/Object.h"
#include <vector>
#include <memory>

class Tabuleiro : public Object {
public:
    Tabuleiro(glm::vec3 pos = glm::vec3(0.0f), 
              glm::vec3 rot = glm::vec3(0.0f), 
              glm::vec3 scl = glm::vec3(1.0f), 
              float angle = 0.0f);
    
    Tabuleiro(glm::vec3 pos, float angle);

    void init();
    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f)) override;

    float getTamanhoCasa() const { return tamanhoCasa; }
    float getTamanhoCentro() const { return tamanhoCentro; }
    float getAlturaBorda() const { return alturaBorda; }

private:
    float tamanhoCentro = 8.0f;
    float espessuraCentro = 0.2f;
    
    float larguraBorda = 0.8f;   
    float alturaBorda = 0.3f;    
    
    float tamanhoCasa = 1.0f;    

    std::vector<std::unique_ptr<Object>> parts;
};

#endif // TABULEIRO_H