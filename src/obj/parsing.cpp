#include <map>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "parsing.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Vertex::Vertex(size_t pos, size_t normal, size_t tex) : pos(pos), normal(normal), tex(tex) {} 

bool operator==(const Vertex& v1, const Vertex& v2) {
  return ( v1.pos == v2.pos ) && ( v1.normal == v2.normal ) && ( v1.tex == v2.tex );
}

std::vector<std::string> split(std::string const& str, const char del) {
  std::vector<std::string> res;

  size_t start = 0;
  size_t end = 0;
  while((start = str.find_first_not_of(del, end)) != std::string::npos) {
    end = str.find(del, start);
    res.push_back(str.substr(start, end));
  }

  return res;
}

Mesh obj::parse(std::string const& obj_path) {
  std::map<VertKey, size_t> vertKey_to_idx;
  std::vector<Vertex> vertices;

  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<unsigned int> indices;

  std::ifstream obj_file( obj_path );
  if (!obj_file.is_open()) {
    throw std::invalid_argument("Cannot open obj file");
  }

  std::string line; 
  while (std::getline(obj_file, line)) {
    std::vector<std::string> tokens = split(line, ' ');

    if (tokens[0] == "v") {
      //vertex
      if (tokens.size() < 4) {
        throw std::runtime_error("Bad vertex definition");
      }
      positions.emplace_back(std::stod(tokens[1]),std::stod(tokens[2]),std::stod(tokens[3]));
    } else if (tokens[0] == "vt") {
      //texture coordinate
      if (tokens.size() < 3) {
        throw std::runtime_error("Bad texture coordinate definition definition");
      }
      texCoords.emplace_back(std::stod(tokens[1]), std::stod(tokens[2]));
    } else if (tokens[0] == "vn") {
      //normal
      if (tokens.size() < 4) {
        throw std::runtime_error("Bad normal definition");
      }
      normals.emplace_back(std::stod(tokens[1]),std::stod(tokens[2]),std::stod(tokens[3]));
    } else if (tokens[0] == "f") {
      //reached faces
      break;
    }
  }

  do {
    std::vector<std::string> tokens = split(line, ' ');

    if (tokens[0] == "f") {
      if (tokens.size() < 4) {
        throw std::runtime_error("Bad face");
      }
      //loop face vertices
      for (int i = 1; i < 4; ++i) {
        size_t vertexIdx, texIdx, normalIdx;
        std::sscanf(tokens[i].c_str(), "%lu/%lu/%lu", &vertexIdx, &texIdx, &normalIdx);
        vertexIdx--;
        texIdx--;
        normalIdx--;

        VertKey key = std::make_tuple(vertexIdx, normalIdx, texIdx);
        auto [it, inserted] = vertKey_to_idx.emplace(key, vertices.size());
        if (inserted) {
          vertices.emplace_back(vertexIdx, normalIdx, texIdx);
        }

        indices.push_back(it->second);
      }
    }
  } while (std::getline(obj_file, line));


  Mesh mesh;

  std::for_each(vertices.begin(), vertices.end(), [&mesh, &positions, &normals, &texCoords](auto vert) {
      mesh.vertices.push_back(vert);

      glm::vec3 pos = positions[vert.pos];
      mesh.positions.push_back(pos.x);
      mesh.positions.push_back(pos.y);
      mesh.positions.push_back(pos.z);

      glm::vec3 normal = normals[vert.normal];
      mesh.normals.push_back(normal.x);
      mesh.normals.push_back(normal.y);
      mesh.normals.push_back(normal.z);

      glm::vec2 tex = texCoords[vert.tex];
      mesh.texCoords.push_back(tex.x);
      mesh.texCoords.push_back(tex.y);
      });
  mesh.indices = indices;

  return mesh;
}
