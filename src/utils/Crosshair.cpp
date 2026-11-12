#include "utils/Crosshair.h"

Crosshair::Crosshair(float width, float height, float size,
                     const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath), screenWidth(width), screenHeight(height) {

    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;

    float vertices[] = {
        centerX - size, centerY, centerX + size, centerY, // Linha horizontal
        centerX, centerY - size, centerX, centerY + size // Linha vertical
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Crosshair::~Crosshair() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Crosshair::draw() {
    glDisable(GL_DEPTH_TEST);

    shader.use();
    glm::mat4 orthoProjection = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
    shader.setMat4("projection", orthoProjection);

    glBindVertexArray(VAO);
    glLineWidth(2.0f);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}