#include "utils/Shadow.h"
#include <GL/glext.h>

Shadow::Shadow(int layers, unsigned int width, unsigned int height,
               const char* vertexPath, const char* fragmentPath)
    : shadowWidth(width), shadowHeight(height),
      depthShader(vertexPath, fragmentPath), maxLayers(layers),
      lightSpaceMatrix(layers, glm::mat4(1.0f)) {

    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, depthArray);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT,
                 shadowWidth, shadowHeight, maxLayers, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, borderColor);
}

Shadow::~Shadow() {
    glDeleteFramebuffers(1, &depthMapFBO);
    glDeleteTextures(1, &depthArray);
}

void Shadow::configureShader(Shader& shader, unsigned int textureUnit) const {
    shader.use();
    shader.setInt("shadowMaps", static_cast<int>(textureUnit));
}

void Shadow::renderDepthMap(int layer, const glm::vec3& lightPos, const std::function<void(Shader&)>& drawScene) {
    glm::mat4 lightProjection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, nearPlane, farPlane);
    glm::mat4 lightView = glm::lookAt(lightPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
    lightSpaceMatrix[layer] = lightProjection * lightView;

    depthShader.use();
    depthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix[layer]);

    glViewport(0, 0, shadowWidth, shadowHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        depthArray, 0, layer);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glClear(GL_DEPTH_BUFFER_BIT);

    drawScene(depthShader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);
}

void Shadow::bind(Shader& shader, unsigned int textureUnit) const {
    shader.use();
    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "lightSpaceMatrix[0]"),
        maxLayers, GL_FALSE, &lightSpaceMatrix[0][0][0]);
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, depthArray);
}