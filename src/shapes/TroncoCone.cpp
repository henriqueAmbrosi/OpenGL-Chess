#include "shapes/TroncoCone.h"
#include <cmath>

TroncoCone::TroncoCone(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float angle, float radiusBottom, float radiusTop, float height, unsigned int sectors)
    : Object(pos, rot, scl, angle) {
    init(radiusBottom, radiusTop, height, sectors);
}

TroncoCone::~TroncoCone() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void TroncoCone::init(float radiusBottom, float radiusTop, float height, unsigned int sectors) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float halfHeight = height / 2.0f;
    float PI = 3.14159265359f;

    for (unsigned int i = 0; i <= 1; ++i) {
        float h = (i == 0) ? -halfHeight : halfHeight;
        float r = (i == 0) ? radiusBottom : radiusTop;
        float t = (i == 0) ? 1.0f : 0.0f;

        for (unsigned int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * 2.0f * PI / sectors;
            float x = r * cosf(sectorAngle);
            float z = r * sinf(sectorAngle);
            float s = (float)j / sectors;

            vertices.push_back(x);
            vertices.push_back(h);
            vertices.push_back(z);
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    for (unsigned int j = 0; j < sectors; ++j) {
        unsigned int top1 = j;
        unsigned int top2 = j + 1;
        unsigned int bottom1 = (sectors + 1) + j;
        unsigned int bottom2 = (sectors + 1) + j + 1;

        indices.push_back(top1);
        indices.push_back(bottom1);
        indices.push_back(top2);

        indices.push_back(top2);
        indices.push_back(bottom1);
        indices.push_back(bottom2);
    }

    // Tampa Superior
    unsigned int topCenterIndex = vertices.size() / 5;
    vertices.push_back(0.0f); vertices.push_back(halfHeight); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(0.5f);

    for (unsigned int j = 0; j <= sectors; ++j) {
        float sectorAngle = j * 2.0f * PI / sectors;
        float x = radiusTop * cosf(sectorAngle);
        float z = radiusTop * sinf(sectorAngle);
        vertices.push_back(x); vertices.push_back(halfHeight); vertices.push_back(z);
        vertices.push_back((radiusTop > 0.0f ? x / radiusTop + 1.0f : 1.0f) * 0.5f);
        vertices.push_back((radiusTop > 0.0f ? z / radiusTop + 1.0f : 1.0f) * 0.5f);
    }

    for (unsigned int j = 0; j < sectors; ++j) {
        indices.push_back(topCenterIndex);
        indices.push_back(topCenterIndex + 1 + j + 1);
        indices.push_back(topCenterIndex + 1 + j);
    }

    // Tampa Inferior
    unsigned int bottomCenterIndex = vertices.size() / 5;
    vertices.push_back(0.0f); vertices.push_back(-halfHeight); vertices.push_back(0.0f);
    vertices.push_back(0.5f); vertices.push_back(0.5f);

    for (unsigned int j = 0; j <= sectors; ++j) {
        float sectorAngle = j * 2.0f * PI / sectors;
        float x = radiusBottom * cosf(sectorAngle);
        float z = radiusBottom * sinf(sectorAngle);
        vertices.push_back(x); vertices.push_back(-halfHeight); vertices.push_back(z);
        vertices.push_back((radiusBottom > 0.0f ? x / radiusBottom + 1.0f : 1.0f) * 0.5f);
        vertices.push_back((radiusBottom > 0.0f ? z / radiusBottom + 1.0f : 1.0f) * 0.5f);
    }

    for (unsigned int j = 0; j < sectors; ++j) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(bottomCenterIndex + 1 + j);
        indices.push_back(bottomCenterIndex + 1 + j + 1);
    }

    indexCount = static_cast<unsigned int>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void TroncoCone::draw(Shader &shader, glm::mat4 model) {
    model = glm::translate(model, position);

    if (glm::length(rotation) > 0.0f)
        model = glm::rotate(model, glm::radians(angle), glm::normalize(rotation));

    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}