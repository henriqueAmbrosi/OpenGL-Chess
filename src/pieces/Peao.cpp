#include "pieces/Peao.h"
#include "shapes/TroncoCone.h"
#include "shapes/Esfera.h"

Peao::Peao(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle)
    : Object(pos, rot, scl, angle)
{
    init();
}

Peao::Peao(glm::vec3 pos, float angle)
    : Object(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), angle)
{
    init();
}

void Peao::init() {
    parts.clear();

    // 1. BASE INFERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.04f, 0.0f),     
        glm::vec3(0.0f, 1.0f, 0.0f),      
        glm::vec3(1.0f, 1.0f, 1.0f),      
        0.0f,                             
        0.22f,                             
        0.18f,                             
        0.07f                              
    ));

    // 2. BASE SUPERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.09f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.18f,                             
        0.16f,                            
        0.04f                              
    ));

    // 3. CORPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.26f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.14f,                             
        0.08f,                            
        0.30f                              
    ));

    // 4. ANEL DO PESCOÇO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.43f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.08f,                            
        0.12f,                            
        0.04f                              
    ));

    // 5. CABEÇA DO PEÃO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 0.53f, 0.0f),  
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.24f, 0.24f, 0.24f),    
        0.0f,
        0.5f    
    ));
}