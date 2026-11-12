#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Shader.h>

class Crosshair {
private:
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    float screenWidth;
    float screenHeight;

public:
    Crosshair(float width = 1024.0f, float height = 768.0f, float size = 10.0f,
              const char* vertexPath = "cursor_vertex.glsl",
              const char* fragmentPath = "cursor_fragment.glsl");
    ~Crosshair();

    Crosshair(const Crosshair&) = delete;
    Crosshair& operator=(const Crosshair&) = delete;

    void draw();
};