#pragma once

#include <glm/glm.hpp>
#include <utils/Camera.h>
#include <utils/Light.h>
#include <pieces/Tabuleiro.h>
#include <unordered_map>

struct GLFWwindow;

class Controls {
private:
    GLFWwindow* window;
    Camera* camera;
    Light* light;
    Tabuleiro* tabuleiro;
    glm::mat4* modelTabuleiro;

    int screenWidth;
    int screenHeight;
    float senseFactor = 15.0f;

    std::unordered_map<int, int> keyStates;
    
    int keyClick(int key);

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
    Controls(GLFWwindow* win, Camera* cam, Light* light, Tabuleiro* tab, glm::mat4* modelTab,
             int width = 1024, int height = 768);

    void update();
};