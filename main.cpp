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

#define senseFactor 15;

double x, y;
float sensitivity = 1.0f;
float yaw = -90.0f;
float pitch = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool intersectPlane(const glm::vec3& ro, const glm::vec3& rd,
    float planeY, float& t) {
    if (std::abs(rd.y) < 1e-6f) return false;
    t = (planeY - ro.y) / rd.y;
    return t >= 0.0f;
}

void viraCamera(float x, float y)
{
    yaw += x * sensitivity;
    pitch += y * sensitivity;
    if(pitch > 89.0f)
    pitch = 89.0f;
    if(pitch < -89.0f)
    pitch = -89.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void processInput(GLFWwindow *window, glm::vec3* position) {
    const float cameraSpeed = 0.15f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        (*position) += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        (*position) -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        (*position) -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        (*position) += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        (*position) += glm::normalize(cameraUp) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        (*position) -= glm::normalize(cameraUp) * cameraSpeed;
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
        GLdouble worldX, worldY, worldZ;

        // Processa input
        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(app.getWindow(), true);
        }
        processInput(app.getWindow(), &position);

        glfwGetCursorPos(app.window, &xrot, &yrot);

        xangle = (xrot - 512) / senseFactor;
        yangle = -(yrot - 384) / senseFactor;
        glfwSetCursorPos(app.window, 1024/2, 768/2);

        // printf("x: %f | y: %f \n", xrot, yrot);

        // Limpa tela e depth buffer
        //glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        
        // model = glm::rotate(model, (angle * (float) glfwGetTime()) / 20, glm::vec3(0.0f, 0.3f, 0.0f));
        // model = glm::rotate(model, (float) glm::radians(zrot), glm::vec3(0.0f, 0.0f, 1.0f));
        // model = glm::rotate(model, (float) glm::radians(xangle), glm::vec3(0.0f, 1.0f, 0.0f));
        // model = glm::rotate(model, (float) glm::radians(yangle), glm::vec3(0.0f, 0.0f, 1.0f));''
        // //model = glm::rotate(model, -60.0f, glm::vec3(0.0f, 0.3f, 0.0f));
        // position += glm::vec3(glm::vec4(pos, 1.0f)  * model);
        glm::mat4 untranslatedModel = glm::mat4(model);
        // model = glm::translate(model, position);

        shader.setMat4("model", model);

        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(position - cameraTarget);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        // Configura view e projection
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                1024.0f / 768.0f,
                                                0.1f, 100.0f);

        viraCamera(xangle, yangle);
        glm::mat4 view = glm::lookAt(position, position + cameraFront, cameraUp);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        if (glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !p1.hasSelectedPiece()) {
            p1.selectPiece(position, cameraFront, model);
        }

        if (p1.hasSelectedPiece() && glfwGetMouseButton(app.getWindow(), GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
            p1.movePiece(position, cameraFront, model);
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
