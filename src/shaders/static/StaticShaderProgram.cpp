#include "StaticShaderProgram.h"
#include <iostream>

StaticShaderProgram::StaticShaderProgram(const std::string &vertexPath, const std::string &fragmentPath)
        : AbstractShaderProgram(vertexPath, fragmentPath) {}

void StaticShaderProgram::loadTransformation(const glm::mat4& matrix) {
    AbstractShaderProgram::loadMatrix4(transformLocation, matrix);
}

void StaticShaderProgram::loadProjectionMatrix(const glm::mat4& matrix) {
    AbstractShaderProgram::loadMatrix4(projectionLocation, matrix);
}

void StaticShaderProgram::loadViewMatrix(const glm::mat4& matrix) {
    AbstractShaderProgram::loadMatrix4(viewLocation, matrix);
}

void StaticShaderProgram::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "normal");
    bindAttribute(2, "textureCoords");
}

void StaticShaderProgram::getAllUniformLocations() {
    this->transformLocation = getUniformLocation("transformationMatrix");
    this->projectionLocation = getUniformLocation("projectionMatrix");
    this->viewLocation = getUniformLocation("viewMatrix");
}
