#pragma once

#include "../AbstractShaderProgram.h"

class Matrix4;

class StaticShaderProgram : public AbstractShaderProgram {
public:
    StaticShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    void loadTransformation(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& matrix);
    void loadViewMatrix(const glm::mat4& matrix);

protected:
    virtual void bindAttributes() override;

    void getAllUniformLocations() override;

    GLuint transformLocation;
    GLuint projectionLocation;
    GLuint viewLocation;
};
