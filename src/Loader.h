#pragma once

#include <vector>
#include <GL/glew.h>

class Loader {
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

public:
    ~Loader();

    GLuint createVAO(std::vector<double> &vertexes, std::vector<double>& normals, std::vector<double>& tex, std::vector<unsigned int> &indices);

private:
    GLuint genVao();
    void unbindVAO();

    void storeDataInAttributeList(GLuint index, int coordSize, const std::vector<double> &data);

    void bindIndicesBuffer(const std::vector<unsigned int> &indices);
};
