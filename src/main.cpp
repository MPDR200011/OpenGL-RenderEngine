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

void prepareCanvas() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void drawVAO(GLuint vaoID) {
    glBindVertexArray(vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

    std::vector<float> vertexes {
            -0.5f,-0.5f, 0,
             0.5f,-0.5f, 0,
             0   , 0.5f, 0
    };

    std::vector<int> indices {
            0,1,2
    };

    float colors[] = {
            1,0,0,
            0,1,0,
            0,0,1,
    };

    GLuint triangle = loader.createVAO(vertexes, indices);

    glBindVertexArray(triangle);

    GLuint colorsVboID;
    glGenBuffers(1, &colorsVboID);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    StaticShaderProgram shader("assets/shaders/quickVertex.glsl", "assets/shaders/quickFragment.glsl");
    shader.init();

    glViewport(0, 0, window.getWidth(), window.getHeight());
    /* Loop until the user closes the window */

    while (!window.shouldClose()) {
        /* Render here */
        prepareCanvas();

        shader.start();

        drawVAO(triangle);

        shader.stop();

        /* Swap front and back buffers */
        window.swapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

