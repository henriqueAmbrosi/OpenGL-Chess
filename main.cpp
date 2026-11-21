#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <Application.h>
#include <utils/Shader.h>
#include <utils/Texture.h>
#include <utils/Light.h>
#include <utils/Shadow.h>
#include <utils/Camera.h>
#include <utils/Crosshair.h>
#include <utils/Skybox.h>
#include <utils/Controls.h>
#include <pieces/Tabuleiro.h>

#include <vector>

void updateSceneLights(std::vector<glm::vec3>& lightPositions,
                       std::vector<glm::vec3>& lightIntensity,
                       const Light& light,
                       const Light& light2) {
    lightPositions[0] = light.position;
    lightPositions[1] = light2.position;
    lightIntensity[0] = glm::vec3(0.7f, 0.7f, 0.7f);
    lightIntensity[1] = glm::vec3(0.8f, 0.7f, 0.7f);
    // Ative para modo balada
    // int tempo = static_cast<int>(glfwGetTime() * 9);
    // lightIntensity[1] = glm::vec3(tempo % 2 * -1.0f, tempo % 3 * -1.0f, tempo % 5 * -1.0f);
}

void setupPieceShader(Shader& shader,
                        const glm::mat4& model,
                        Camera& camera,
                        float aspect,
                        Shadow& shadow,
                        const std::vector<glm::vec3>& lightPositions,
                        const std::vector<glm::vec3>& lightIntensity,
                        Texture& tex1,
                        Texture& tex2) {
    shader.use();
    shader.setMat4("model", model);
    shader.setVec3("viewPos", camera.position);
    shader.setFloat("specularStrength", 6.0f);
    camera.applyUniforms(shader, aspect);

    shader.setInt("size", 2);
    glUniform3fv(glGetUniformLocation(shader.ID, "lightPos[0]"), 2, glm::value_ptr(lightPositions[0]));
    glUniform3fv(glGetUniformLocation(shader.ID, "lightIntensity[0]"), 2, glm::value_ptr(lightIntensity[0]));
    shadow.bind(shader, 2);

    tex1.bind(1);
    tex2.bind(4);
}

void setupBoardShader(Shader& boardShader,
                      const glm::mat4& model,
                      Camera& camera,
                      float aspect,
                      Shadow& shadow,
                      const std::vector<glm::vec3>& lightPositions,
                      const std::vector<glm::vec3>& lightIntensity,
                      Texture& tex1,
                      Texture& boardMarble) {
    boardShader.use();
    boardShader.setInt("size", 2);
    glUniform3fv(glGetUniformLocation(boardShader.ID, "lightPos[0]"), 2, glm::value_ptr(lightPositions[0]));
    glUniform3fv(glGetUniformLocation(boardShader.ID, "lightIntensity[0]"), 2, glm::value_ptr(lightIntensity[0]));
    boardShader.setMat4("model", model);
    boardShader.setVec3("viewPos", camera.position);
    boardShader.setFloat("specularStrength", 0.5f);
    shadow.bind(boardShader, 2);
    camera.applyUniforms(boardShader, aspect);

    tex1.bind(0);
    boardMarble.bind(3);
}

int main() {
    const int WIDTH = 1024;
    const int HEIGHT = 768;
    std::vector<glm::vec3> lightPositions(10);
    std::vector<glm::vec3> lightIntensity(10);

    // Inicializa janela e OpenGL
    Application app(WIDTH, HEIGHT, "Chess");
    if (!app.init()) return -1;

    glEnable(GL_DEPTH_TEST);

    // Shaders e texturas
    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Texture tex1("textures/xadrez2x2.png");
    Texture tex2("textures/opal.png");
    Texture tex3("textures/marble.jpg");
    Texture tex4("textures/black_marble.png");
    Shader boardShader("shaders/vertex.glsl", "shaders/board_fragment.glsl");

    // Objetos da cena e auxiliares
    Tabuleiro p1(glm::vec3(0.0f, -4.0f, 0.0f), 0.0f);
    p1.scale = glm::vec3(2.5f, 2.5f, 2.5f);
    glm::mat4 modelTabuleiro = glm::mat4(1.0f);

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
    Light light(glm::vec3(8.0f, 12.0f, 24.0f), 0);
    Light light2(glm::vec3(8.0f, 4.0f, 12.0f), 0);
    Shadow shadow(10, 4096, 4096);
    Crosshair crosshair(WIDTH, HEIGHT);
    Skybox skybox(90.0f);
    Controls controls(app.getWindow(), &camera, &light, &p1, &modelTabuleiro, WIDTH, HEIGHT);

    // Configura slots de textura
    shader.use();
    shader.setInt("opal", 1);
    shader.setInt("dark_marble", 4);
    shadow.configureShader(shader, 2);
    
    boardShader.use();
    boardShader.setInt("xadrez", 0);
    boardShader.setInt("marble", 3);
    shadow.configureShader(boardShader, 2);

    // Loop principal
    glDepthFunc(GL_LEQUAL);
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
        shadow.renderDepthMap(0, light.getPosition(), [&](Shader& depthShader) {
            p1.draw(depthShader, model);
        });
        shadow.renderDepthMap(1, light2.getPosition(), [&](Shader& depthShader) {
            p1.draw(depthShader, model);
        });

        // Renderiza a cena
        app.framebuffer_size_callback(app.getWindow(), WIDTH, HEIGHT);
        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float aspect = static_cast<float>(WIDTH) / HEIGHT;
        skybox.draw(camera.getViewMatrix(), camera.getProjectionMatrix(aspect));

        updateSceneLights(lightPositions, lightIntensity, light, light2);
        setupBoardShader(boardShader, model, camera, aspect, shadow, lightPositions, lightIntensity,
                         tex1, tex3);
        setupPieceShader(shader, model, camera, aspect, shadow, lightPositions, lightIntensity,
                         tex2, tex4);

        shader.use();

        p1.draw(shader, boardShader, model);

        light.draw(camera.getViewMatrix(), camera.getProjectionMatrix(aspect));
        light2.draw(camera.getViewMatrix(), camera.getProjectionMatrix(aspect));

        crosshair.draw();

        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}