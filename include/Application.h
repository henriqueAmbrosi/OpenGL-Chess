#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Application {
private:
    int width, height;
    std::string title;

public:
    GLFWwindow* window;

    Application(int w, int h, const std::string& t);
    ~Application();

    bool init();       // Inicializa GLFW/GLEW
    void run();        // Loop principal
    GLFWwindow* getWindow() const { return window; }
    void setTitle(const std::string& t);

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif
