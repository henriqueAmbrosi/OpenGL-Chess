#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    double xrot, yrot, xangle, yangle, zrot, zangle;
        
    // Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

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
            zrot += 1;
        }
        if (glfwGetKey(app.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            zrot -= 1;
        }

        glfwGetCursorPos(app.window, &xrot, &yrot);

        if (glfwGetKey(app.getWindow(), GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS) {
            xangle += (xrot - 512) / senseFactor;
            yangle -= (yrot - 384) / senseFactor;
            glfwSetCursorPos(app.window, 1024/2, 768/2);
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

        model = glm::translate(model, position);

        shader.setMat4("model", model);

        // Configura view e projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f,
                                                0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.0f, -12.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

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