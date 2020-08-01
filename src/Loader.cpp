#include "Loader.h"


GLuint Loader::createVAO(std::vector<float> &vertexes, std::vector<float>& normals, std::vector<float>& tex, std::vector<unsigned int> &indices) {
    GLuint vaoID = genVao();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, vertexes);
    storeDataInAttributeList(1, 3, normals);
    storeDataInAttributeList(2, 2, tex);
    glBindVertexArray(0);
    unbindVAO();

    return vaoID;
}

void Loader::bindIndicesBuffer(const std::vector<unsigned int> &indices) {
    GLuint indicesVboID;
    glGenBuffers(1, &indicesVboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
}

void Loader::storeDataInAttributeList(GLuint index, int coordSize, const std::vector<float> &data) {
    GLuint vertexVboID;
    glGenBuffers(1, &vertexVboID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(index, coordSize, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Loader::genVao() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Loader::~Loader() {
    glDeleteBuffers((GLsizei) vbos.size(), &vbos[0]);
    glDeleteVertexArrays((GLsizei) vaos.size(), &vaos[0]);
}
