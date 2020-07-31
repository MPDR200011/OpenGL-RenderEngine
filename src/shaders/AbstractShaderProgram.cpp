#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "AbstractShaderProgram.h"
#include <exception>

AbstractShaderProgram::AbstractShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
    this->vertexShaderID = loadShader(vertexPath, GL_VERTEX_SHADER);
    this->fragmentShaderID = loadShader(fragmentPath, GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);
}

AbstractShaderProgram::~AbstractShaderProgram() {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

void AbstractShaderProgram::init() {
    this->bindAttributes();
    this->getAllUniformLocations();
}

void AbstractShaderProgram::start() {
    glUseProgram(programID);
}

void AbstractShaderProgram::stop() {
    glUseProgram(0);
}

void AbstractShaderProgram::bindAttributes() {
    return;
}

void AbstractShaderProgram::getAllUniformLocations() {
    return;
}

GLint AbstractShaderProgram::getUniformLocation(const std::string &varName) {
    return glGetUniformLocation(programID, varName.c_str());
}

void AbstractShaderProgram::bindAttribute(GLuint attribIndex, const std::string &varName) {
    glBindAttribLocation(programID, attribIndex, varName.c_str());
}

void AbstractShaderProgram::loadFloat(GLint location, float value) {
    glUniform1f(location, value);
}

void AbstractShaderProgram::loadMatrix4(GLint location, const glm::mat4& matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

GLuint AbstractShaderProgram::loadShader(const std::string &path, GLenum type) {
    GLuint id = glCreateShader(type);
    std::ifstream shaderSource(path);
    if (!shaderSource.is_open()) {
        std::cerr << "File " << path << " does not exist." << std::endl;
    }

    std::stringstream ss;

    std::string line;
    while (getline(shaderSource, line)){
        ss << line << "\n";
    }
    shaderSource.close();

    std::string sourceString = ss.str();
    const char * sourcePtr = sourceString.c_str();
    glShaderSource(id, 1, &sourcePtr, nullptr);
    glCompileShader(id);

    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::cerr << "Shader compilation failed." << std::endl;

        GLint logSize;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);

        char* log = new char[logSize];
        int temp;
        glGetShaderInfoLog(id, logSize, &temp, log);
        std::cerr << log << std::endl;
        
        delete[] log;
    } 
    
    return id;
}

