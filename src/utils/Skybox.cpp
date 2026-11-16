#include "utils/Skybox.h"
#include <utils/stb_image.h>
#include <iostream>

namespace {
constexpr int kFaceSize = 512;
// Horizontal cross (2048x1536): +X, -X, +Y, -Y, +Z, -Z
constexpr int kFaceX[6] = {2, 0, 1, 1, 1, 3};
constexpr int kFaceY[6] = {1, 1, 0, 2, 1, 1};
} // namespace

unsigned int Skybox::loadCubemap(const char* path) {
    stbi_set_flip_vertically_on_load(false);

    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    for (unsigned int i = 0; i < 6; ++i) {
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, kFaceX[i] * kFaceSize);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, kFaceY[i] * kFaceSize);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                     kFaceSize, kFaceSize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);
    return textureID;
}

Skybox::Skybox(float size, const char* cubeMapAssetPath,
               const char* vertexPath, const char* fragmentPath)
    : shader(vertexPath, fragmentPath),
      cube(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(size), 0.0f),
      cubemapID(loadCubemap(cubeMapAssetPath)) {}

Skybox::~Skybox() {
    if (cubemapID != 0)
        glDeleteTextures(1, &cubemapID);
}

void Skybox::draw(const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setInt("skybox", 0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

    cube.draw(shader, glm::mat4(1.0f));
}