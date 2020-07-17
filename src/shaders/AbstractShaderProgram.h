#ifndef OPENGL_TESTS_ABSTRACTSHADER_H
#define OPENGL_TESTS_ABSTRACTSHADER_H


#include <string>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class AbstractShaderProgram {
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

public:
    AbstractShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);
    ~AbstractShaderProgram();

    void init();

    void start();
    void stop();

protected:
    virtual void bindAttributes() = 0;
    virtual void getAllUniformLocations() = 0;

    GLint getUniformLocation(const std::string &varName);
    void bindAttribute(GLuint attribIndex, const std::string &varName);

    static void loadFloat(GLint location, float value);
    static void loadMatrix4(GLint location, const glm::mat4& matrix);
    static GLuint loadShader(const std::string &path, GLenum type);


};


#endif //OPENGL_TESTS_ABSTRACTSHADER_H
