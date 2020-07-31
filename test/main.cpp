#include <iostream>
#include "obj/parsing.hpp"

int main() {
  Mesh mesh = obj::parse("cube.obj");

  std::cout << mesh.vertices.size() << std::endl;
  std::cout << mesh.indices.size() << std::endl;
  std::cout << mesh.positions.size() << std::endl;
  std::cout << mesh.normals.size() << std::endl;
  std::cout << mesh.texCoords.size() << std::endl;

  for (size_t i = 0; i < mesh.positions.size(); i+=3) {
    std::printf("%lu: %lf %lf %lf\n", i/3, mesh.positions[i],mesh.positions[i+1],mesh.positions[i+2]);
  }

  for (size_t i = 0; i < mesh.indices.size(); i+=3) {
    std::printf("%lu: %lu %lu %lu\n", i/3, mesh.indices[i],mesh.indices[i+1],mesh.indices[i+2]);
  }

  return 0;
}
