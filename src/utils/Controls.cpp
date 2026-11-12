#include "utils/Controls.h"
#include <GLFW/glfw3.h>

Controls::Controls(GLFWwindow* win, Camera* cam, Light* light, Tabuleiro* tab, glm::mat4* modelTab,
                   int width, int height)
    : window(win), camera(cam), light(light), tabuleiro(tab), modelTabuleiro(modelTab),
      screenWidth(width), screenHeight(height) {

    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

int Controls::keyClick(int key) {
    int state = glfwGetKey(window, key);

    if (state == GLFW_PRESS && !keyStates[key]) {
        keyStates[key] = 1;
        return 1;
    } else if (state == GLFW_RELEASE) {
        keyStates[key] = 0;
    }

    return 0;
}

void Controls::update() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->move(Movement::FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->move(Movement::BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->move(Movement::LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->move(Movement::RIGHT);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->move(Movement::UP);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera->move(Movement::DOWN);
    
    // Light controls
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        light->move(Movement::FORWARD);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        light->move(Movement::BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        light->move(Movement::LEFT);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        light->move(Movement::RIGHT);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        light->move(Movement::UP);
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        light->move(Movement::DOWN);
    if (keyClick(GLFW_KEY_L))
        light->swapMode();


    double xrot, yrot;
    glfwGetCursorPos(window, &xrot, &yrot);

    float halfW = screenWidth / 2.0f;
    float halfH = screenHeight / 2.0f;

    float xangle = static_cast<float>(xrot - halfW) / senseFactor;
    float yangle = -static_cast<float>(yrot - halfH) / senseFactor;

    glfwSetCursorPos(window, halfW, halfH);
    camera->rotate(xangle, yangle);
}

void Controls::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        auto* controls = static_cast<Controls*>(glfwGetWindowUserPointer(window));

        if (!controls->tabuleiro->hasSelectedPiece()) {
            controls->tabuleiro->selectPiece(
                controls->camera->position,
                controls->camera->front,
                *(controls->modelTabuleiro)
            );
        } else {
            controls->tabuleiro->movePiece(
                controls->camera->position,
                controls->camera->front,
                *(controls->modelTabuleiro)
            );
        }
    }
}