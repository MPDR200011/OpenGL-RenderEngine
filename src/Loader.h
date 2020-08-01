#pragma once

#include <vector>
#include <GL/glew.h>

class Loader {
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

public:
    ~Loader();

    GLuint createVAO(std::vector<float> &vertexes, std::vector<float>& normals, std::vector<float>& tex, std::vector<unsigned int> &indices);

private:
    GLuint genVao();
    void unbindVAO();

    void storeDataInAttributeList(GLuint index, int coordSize, const std::vector<float> &data);

    void bindIndicesBuffer(const std::vector<unsigned int> &indices);
};
