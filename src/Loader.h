#ifndef OPENGL_TESTS_LOADER_H
#define OPENGL_TESTS_LOADER_H

#include <vector>
#include <GL/glew.h>

class Loader {
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

public:
    ~Loader();

    GLuint createVAO(std::vector<double> &vertexes, std::vector<int> &indices);

private:
    GLuint genVao();
    void unbindVAO();

    void storeDataInAttributeList(GLuint index, int coordSize, const std::vector<double> &data);

    void bindIndicesBuffer(const std::vector<int> &indices);
};

#endif //OPENGL_TESTS_LOADER_H
