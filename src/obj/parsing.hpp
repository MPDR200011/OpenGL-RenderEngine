#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <optional>

struct Vertex {
  explicit Vertex() {};
  Vertex(size_t, size_t, size_t);

  std::optional<size_t> next_copy_idx;

  size_t pos;
  size_t normal;
  size_t tex;
};
bool operator==(Vertex const& v1,Vertex const& v2);

struct Mesh {
  std::vector<Vertex> vertices;

  std::vector<unsigned int> indices;
  std::vector<double> positions;
  std::vector<double> normals;
  std::vector<double> texCoords;
};

namespace obj {
  Mesh parse(std::string const& obj_path);
}

