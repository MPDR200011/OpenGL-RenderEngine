#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <tuple>
#include <optional>

struct Vertex {
  explicit Vertex() {};
  Vertex(size_t, size_t, size_t);

  size_t pos;
  size_t normal;
  size_t tex;
};
bool operator==(Vertex const& v1,Vertex const& v2);

typedef std::tuple<size_t, size_t, size_t> VertKey;

struct Mesh {
  std::vector<Vertex> vertices;

  std::vector<unsigned int> indices;
  std::vector<float> positions;
  std::vector<float> normals;
  std::vector<float> texCoords;
};

namespace obj {
  Mesh parse(std::string const& obj_path);
}

