#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace sb {
struct Effect {
  std::string name;
  bool has_geometry;
  bool is_compute;
  void *GpuData;
};

struct Mesh {
  std::vector<glm::vec3> positions;
  glm::vec3 min;
  glm::vec3 max;
  std::vector<glm::vec4> colours;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> tex_coords;
  std::vector<unsigned int> indices;
  void *GpuData;
};

class data_ops {
public:
  static Mesh *GetMesh(const std::string &path);
  static Effect *GetEffect(const std::string &path);
};
} // namespace sb
