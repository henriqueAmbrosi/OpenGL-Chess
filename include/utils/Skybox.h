#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <utils/Shader.h>
#include <shapes/Cube.h>

class Skybox {
private:
    Shader shader;
    Cube cube;
    unsigned int cubemapID;

    static unsigned int loadCubemap(const char* path);

public:
    Skybox(float size = 500.0f,
           const char* cubeMapAssetPath = "textures/Cubemap_Sky_15-512x512.png",
           const char* vertexPath = "shaders/skybox_vertex.glsl",
           const char* fragmentPath = "shaders/skybox_fragment.glsl");
    ~Skybox();

    Skybox(const Skybox&) = delete;
    Skybox& operator=(const Skybox&) = delete;

    void draw(const glm::mat4& view, const glm::mat4& projection);
};