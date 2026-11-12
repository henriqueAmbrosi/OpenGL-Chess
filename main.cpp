#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Application.h>
#include <utils/Shader.h>
#include <utils/Texture.h>
#include <utils/Light.h>
#include <utils/Shadow.h>
#include <utils/Camera.h>
#include <utils/Crosshair.h>
#include <utils/Controls.h>
#include <pieces/Tabuleiro.h>

int main() {
    const int WIDTH = 1024;
    const int HEIGHT = 768;

    // Inicializa janela e OpenGL
    Application app(WIDTH, HEIGHT, "Chess");
    if (!app.init()) return -1;

    glEnable(GL_DEPTH_TEST);

    // Shaders e texturas
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Texture tex1("textures/xadrez2x2.png");
    Texture tex2("textures/madeira.png");

    // Objetos da cena e auxiliares
    Tabuleiro p1(glm::vec3(0.0f, -4.0f, 0.0f), 0.0f);
    p1.scale = glm::vec3(2.5f, 2.5f, 2.5f);
    glm::mat4 modelTabuleiro = glm::mat4(1.0f);

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
    Light light(glm::vec3(8.0f, 12.0f, 24.0f), 0);
    Shadow shadow(2048, 2048);
    Crosshair crosshair(WIDTH, HEIGHT);
    Controls controls(app.getWindow(), &camera, &light, &p1, &modelTabuleiro, WIDTH, HEIGHT);

    // Configura slots de textura
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    shadow.configureShader(shader, 2);

    // Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        controls.update();

        glm::mat4 model = glm::mat4(1.0f);

        // Atualiza a matriz do tabuleiro para o raycasting do clique
        modelTabuleiro = glm::mat4(1.0f);
        modelTabuleiro = glm::translate(modelTabuleiro, p1.position);
        if (glm::length(p1.rotation) > 0.0f)
            modelTabuleiro = glm::rotate(modelTabuleiro, glm::radians(p1.angle), glm::normalize(p1.rotation));
        modelTabuleiro = glm::scale(modelTabuleiro, p1.scale);

        // Atualiza luz e gera depth map das sombras
        light.update();
        shadow.renderDepthMap(light.getPosition(), [&](Shader& depthShader) {
            p1.draw(depthShader, model);
        });

        // Renderiza a cena
        app.framebuffer_size_callback(app.getWindow(), WIDTH, HEIGHT);
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMat4("model", model);

        camera.applyUniforms(shader, static_cast<float>(WIDTH) / HEIGHT);
        light.applyUniforms(shader);
        shadow.bind(shader, 2);

        tex1.bind(0);
        tex2.bind(1);

        p1.draw(shader, model);

        float aspect = static_cast<float>(WIDTH) / HEIGHT;
        light.draw(camera.getViewMatrix(), camera.getProjectionMatrix(aspect));

        crosshair.draw();

        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}