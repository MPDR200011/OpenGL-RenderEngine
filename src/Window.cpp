#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.hpp"

Window::Window(unsigned width, unsigned height, std::string title) : 
  width(width), height(height), title(title)
{
  if (!glfwInit()) {
    throw std::runtime_error("glfwInit() failed.");
  }

  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!this->window) {
    glfwTerminate();
    throw std::runtime_error("glfw failed window creation.");
  }

  regenProjection();

  glfwMakeContextCurrent(this->window);
}

void Window::regenProjection() {
  this->projectionMatrix = glm::perspectiveFov(
      glm::pi<float>() / 2, (float)getWidth(),
      (float)getHeight(), 1.0F, 500.0F);
}

bool Window::shouldClose() const {
  return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
  glfwSwapBuffers(window);
}

unsigned Window::getWidth() const {
  return width;
}
unsigned Window::getHeight() const {
  return height;
}

glm::mat4 Window::getProjectionMatrix() const {
  return projectionMatrix;
}
