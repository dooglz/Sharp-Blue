#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


struct Mesh{
  std::vector<glm::vec3> positions;
  glm::vec3 min;
  glm::vec3 max;
  std::vector<glm::vec4> colours;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> tex_coords;
  std::vector<unsigned int> indices;
  void* GpuData;
};

namespace sb {
class data_ops {
public:
  static Mesh* GetMesh(const std::string& path);
};
}
