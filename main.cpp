#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>
#include <glm/trigonometric.hpp>
#include <utils/Shader.h>
#include <Application.h>
#include <shapes/Cube.h>
#include <pieces/Tabuleiro.h>
#include <pieces/Peao.h>
#include <pieces/Cavalo.h>
#include <pieces/Torre.h>
#include <pieces/Bispo.h>
#include <pieces/Rei.h>
#include <pieces/Rainha.h>
#include <utils/Texture.h>
#include <iostream>

#define cameraSpeed 0.1;
#define senseFactor 15;

double x, y;

bool intersectPlane(const glm::vec3& ro, const glm::vec3& rd,
    float planeY, float& t) {
    if (std::abs(rd.y) < 1e-6f) return false;
    t = (planeY - ro.y) / rd.y;
    return t >= 0.0f;
}

int main() {
    // Cria janela e inicializa OpenGL
    Application app(1024, 768, "Chess");
    if (!app.init()) return -1;

    // Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    // Carrega texturas
    Texture tex1("textures/xadrez2x2.png");
    Texture tex2("textures/madeira.png");

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // Cria cubos com posições diferentes
    Cube cube2(glm::vec3(2.0f, 0.0f, -2.5f));
    Cube cube3(glm::vec3(-2.0f, 1.0f, -4.0f));
    Cube cube4(glm::vec3(-3.0f, -1.0f, 3.0f));
    Cube cube5(glm::vec3(-4.0f, 0.0f, 0.0f));


    Tabuleiro p1(glm::vec3(0.0f, -4.0f, 0.0f), 0.0f);
    p1.scale = glm::vec3(2.5f, 2.5f, 2.5f);

    // Ativa depth test
    glEnable(GL_DEPTH_TEST);

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    double xrot, yrot, xangle, yangle, zrot;        
    // Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
        GLdouble worldX, worldY, worldZ;

        // Processa input
        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(app.getWindow(), true);
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            pos.z += cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            pos.z -= cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            pos.x += cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            pos.x -= cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
            pos.y -= cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_C) == GLFW_PRESS) {
            pos.y += cameraSpeed;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            zrot -= 1;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            zrot += 1;
        }

        glfwGetCursorPos(app.window, &xrot, &yrot);

        if (glfwGetKey(app.getWindow(), GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) {
            xangle += (xrot - 512) / senseFactor;
            yangle -= (yrot - 384) / senseFactor;
            glfwSetCursorPos(app.window, 1024/2, 768/2);
            glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        // printf("x: %f | y: %f \n", xrot, yrot);

        // Limpa tela e depth buffer
        //glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        
        // model = glm::rotate(model, (angle * (float) glfwGetTime()) / 20, glm::vec3(0.0f, 0.3f, 0.0f));
        model = glm::rotate(model, (float) glm::radians(zrot), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::rotate(model, (float) glm::radians(xangle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, (float) glm::radians(yangle), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::rotate(model, -60.0f, glm::vec3(0.0f, 0.3f, 0.0f));
        position += glm::vec3(glm::vec4(pos, 1.0f)  * model);
        glm::mat4 untranslatedModel = glm::mat4(model);
        model = glm::translate(model, position);

        shader.setMat4("model", model);

        // Configura view e projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                1024.0f / 768.0f,
                                                0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.0f, -12.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        int w, h;
        glfwGetFramebufferSize(app.getWindow(), &w, &h);
        // OpenGL: (0,0) is bottom-left; GLFW cursor is top-left
        float xx = (2.0f * static_cast<float>(xrot)) / w - 1.0f;
        float yy = 1.0f - (2.0f * static_cast<float>(yrot)) / h;
        glm::mat4 invVP = glm::inverse(projection * view);
        glm::vec4 nearPoint = invVP * glm::vec4(xx, yy, -1.0f, 1.0f);
        glm::vec4 farPoint  = invVP * glm::vec4(xx, yy,  1.0f, 1.0f);
        nearPoint /= nearPoint.w;
        farPoint  /= farPoint.w;
        glm::vec3 rayOrigin = glm::vec3(nearPoint);
        glm::vec3 ray = glm::normalize(glm::vec3(farPoint - nearPoint));

        if (glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !p1.hasSelectedPiece()) {
            printf("Selecting piece\n");
            p1.selectPiece(rayOrigin, ray, untranslatedModel);
        }

        if (p1.hasSelectedPiece() && glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
            p1.movePiece(rayOrigin, ray, untranslatedModel);
        }

        // Bind texturas
        tex1.bind(0);
        tex2.bind(1);

        // Desenha logo banrisul

        p1.draw(shader, model);


        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
