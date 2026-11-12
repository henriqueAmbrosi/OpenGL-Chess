#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utils/Shader.h>
#include <functional>

class Shadow {
private:
    unsigned int depthMapFBO;
    unsigned int depthMap;
    unsigned int shadowWidth;
    unsigned int shadowHeight;
    Shader depthShader;
    glm::mat4 lightSpaceMatrix;

public:
    glm::vec3 target = glm::vec3(0.0f, -4.0f, 0.0f);
    float orthoSize = 15.0f;
    float nearPlane = 1.0f;
    float farPlane = 200.0f;

    Shadow(unsigned int width = 2048, unsigned int height = 2048,
           const char* vertexPath = "depth_vertex.glsl",
           const char* fragmentPath = "depth_fragment.glsl");
    ~Shadow();

    void configureShader(Shader& shader, unsigned int textureUnit = 2) const;

    void renderDepthMap(const glm::vec3& lightPos, const std::function<void(Shader&)>& drawScene);

    void bind(Shader& shader, unsigned int textureUnit = 2) const;
};