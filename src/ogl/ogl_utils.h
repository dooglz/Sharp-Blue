#pragma once

#include "data_ops.h"
namespace sb {
namespace ogl {
void LoadModel(Mesh *msh);
void LoadEffect(Effect *e, const std::string &vert, const std::string &frag, const std::string &geom);
void Render(Mesh *msh, Effect *eff, glm::mat4 MVP);
} // namespace ogl
} // namespace sb