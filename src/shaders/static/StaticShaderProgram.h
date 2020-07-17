#ifndef OPENGL_TESTS_STATICSHADERPROGRAM_H
#define OPENGL_TESTS_STATICSHADERPROGRAM_H

#include "../AbstractShaderProgram.h"

class Matrix4;

class StaticShaderProgram : public AbstractShaderProgram {
public:
    StaticShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    void loadTransformation(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& matrix);

protected:
    virtual void bindAttributes() override;

    void getAllUniformLocations() override;

    GLuint transformLocation;
    GLuint viewLocation;
};


#endif //OPENGL_TESTS_STATICSHADERPROGRAM_H
