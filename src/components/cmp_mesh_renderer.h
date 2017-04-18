#pragma once
#include "../Entity.h"

namespace sb {
class cmp_mesh_renderer : public Component {
protected:
  void *MeshData;

public:
  cmp_mesh_renderer();
  void SetMesh(const std::string &path);

  void Render() override;
};
}
