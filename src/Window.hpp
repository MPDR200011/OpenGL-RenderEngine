#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(unsigned width, unsigned height, std::string title);

    bool shouldClose();
    void swapBuffers();

    unsigned getWidth();
    unsigned getHeight();

private:
    unsigned width;
    unsigned height;
    std::string title;
    GLFWwindow *window;
};