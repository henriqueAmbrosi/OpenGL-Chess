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
        glm::vec3(0.0f, 0.1f, 0.0f),     
        glm::vec3(0.0f, 1.0f, 0.0f),      
        glm::vec3(1.0f, 1.0f, 1.0f),      
        0.0f,                             
        0.6f,                             
        0.5f,                             
        0.2f                              
    ));

    // 2. BASE SUPERIOR
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.25f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.5f,                             
        0.45f,                            
        0.1f                              
    ));

    // 3. CORPO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 0.75f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.4f,                             
        0.22f,                            
        0.9f                              
    ));

    // 4. ANEL DO PESCOÇO
    parts.push_back(std::make_unique<TroncoCone>(
        glm::vec3(0.0f, 1.25f, 0.0f),    
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        0.0f,
        0.22f,                            
        0.32f,                            
        0.1f                              
    ));

    // 5. CABEÇA DO PEÃO
    parts.push_back(std::make_unique<Esfera>(
        glm::vec3(0.0f, 1.55f, 0.0f),  
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.7f, 0.7f, 0.7f),    
        0.0f,
        0.5f    
    ));
}
