#include <stdexcept>
#include "Window.hpp"

Window::Window(unsigned width, unsigned height, std::string title) {
    this->width = width;
    this->height = height;
    this->title = title;

    if (!glfwInit()) {
        throw std::runtime_error("glfwInit() failed.");
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("glfw failed window creation.");
    }

    glfwMakeContextCurrent(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

unsigned Window::getWidth() {
    return width;
}
unsigned Window::getHeight() {
    return height;
}