#pragma once
#include "../Entity.h"

namespace sb {
struct Effect;
struct Mesh;

class cmp_mesh_renderer : public Component {
protected:
  Mesh *mesh;
  Effect *effect;
  void from_json(const nlohmann::json &j);

public:
  cmp_mesh_renderer();
  void SetMesh(const std::string &path);
  void SetEffect(const std::string &path);
  void Render() override;
};
} // namespace sb
