#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Movement.h>
#include <utils/Shader.h>
#include <shapes/Esfera.h>


class Light {
private:
    Shader lightShader;
    Esfera sphere;

public:
    glm::vec3 position;
    int mode; // 0 = Spinning, 1 = Free control

    float speed = 0.5f;
    float radius = 20.0f;
    float height = 12.0f;
    float size = 0.5f;

    Light(glm::vec3 initialPos = glm::vec3(8.0f, 12.0f, 24.0f), int initialMode = 0,
          const char* vertexPath = "shaders/light_vertex.glsl",
          const char* fragmentPath = "shaders/light_fragment.glsl");

    Light(const Light&) = delete;
    Light& operator=(const Light&) = delete;

    void update();
    void applyUniforms(Shader& shader) const;
    void draw(const glm::mat4& view, const glm::mat4& projection);

    void swapMode();
    void move(Movement direction);

    glm::vec3 getPosition() const { return position; }
};

#endif // LIGHT_H