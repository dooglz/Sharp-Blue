//
// Created by Sam Serrels on 01/04/2017.
//

#include "cmp_mesh_renderer.h"
#include <Entity.h>
#include <Renderer.h>
#include <data_ops.h>

sb::cmp_mesh_renderer::cmp_mesh_renderer() : Component("Mesh Renderer") {}

void sb::cmp_mesh_renderer::SetMesh(const std::string &path) { MeshData = data_ops::GetMesh(path); }

void sb::cmp_mesh_renderer::Render() {
  Component::Render();
  Renderer::Render(MeshData, glm::mat4(), Renderer::RenderFlags());
}
