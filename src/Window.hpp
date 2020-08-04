#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

class Window {
public:
    Window(unsigned width, unsigned height, std::string title);

    void regenProjection();

    bool shouldClose() const;
    void swapBuffers();

    unsigned getWidth() const;
    unsigned getHeight() const;

    glm::mat4 getProjectionMatrix() const;

private:
    unsigned width;
    unsigned height;
    std::string title;
    glm::mat4 projectionMatrix;
    GLFWwindow *window;
};
