#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include "Window.hpp"
#include "Loader.h"
#include "shaders/static/StaticShaderProgram.h"
#include "obj/parsing.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

void prepareCanvas() {
  glEnable(GL_DEPTH_TEST);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void drawVAO(GLuint vaoID, int vertexCount) {
  glBindVertexArray(vaoID);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}

int main() {

  Window window(1280, 720, "OpenGL test");

  /* Make the window's context current */

  if (glewInit() != GLEW_OK) {
    std::cerr << "Glew failed to init!" << std::endl;
    exit(1);
  }

  Loader loader;

  Mesh cubeMesh = obj::parse("assets/objs/sphere.obj");

  GLuint cube = loader.createVAO(cubeMesh.positions, cubeMesh.normals, cubeMesh.texCoords, cubeMesh.indices);

  glm::mat4 trans = glm::identity<glm::mat4>();
  trans = glm::translate(trans, {0,0,-3});
//  trans = glm::rotate(trans, 1.0F, {0,1,0});
//  trans = glm::rotate(trans, 1.0F, {0,0,1});

  std::cout << glm::to_string(trans) << std::endl;

  glm::mat4 view = glm::perspectiveFov(glm::pi<float>() / 2, (float) window.getWidth(), (float)window.getHeight(), 1.0F, 500.0F);
  //view = glm::translate(view, {0,0,3});
  std::cout << glm::to_string(view) << std::endl;


  glBindVertexArray(cube);

  StaticShaderProgram shader("assets/shaders/static.vert", "assets/shaders/static.frag");
  shader.init();

  glViewport(0, 0, window.getWidth(), window.getHeight());

  /* Loop until the user closes the window */
  while (!window.shouldClose()) {
    trans = glm::rotate(trans, 0.01F, { 0.0, 1.0, 0.0 });
    trans = glm::rotate(trans, 0.01F, { 0.0, 0.0, 1.0 });
    /* Render here */
    prepareCanvas();

    shader.start();
    shader.loadTransformation(trans);
    shader.loadProjectionMatrix(view);
    drawVAO(cube, cubeMesh.indices.size());

    shader.stop();

    /* Swap front and back buffers */
    window.swapBuffers();

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

