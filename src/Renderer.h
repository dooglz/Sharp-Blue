#pragma once
#include <glm/glm.hpp>

namespace sb {
class Renderer {
public:
  struct RenderFlags {
    bool translucent = false;
    bool castShadow = true;
    bool receiveShadow = true;
    bool movable = true;
  };
  enum LIGHTTYPE { AMBIENT, DIRECTIONAL, POINT, SPOT, AREA };
  struct LightData {
    LIGHTTYPE type = POINT;
    float start = 0.f, end = 10.f, falloff = 1.f, arc = 60.f, cone = 40.f;
    glm::vec3 colour = glm::vec3(0.f);
  };
  static void AddLight(const LightData &ld, const glm::vec3 &position, const glm::quat &rot);
  static void Render(void *MeshData, const glm::mat4 &MVP, const RenderFlags &Flags);
  static void Dispatch();
};
}
