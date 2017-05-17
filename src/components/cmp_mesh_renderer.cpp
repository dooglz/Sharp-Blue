//
// Created by Sam Serrels on 01/04/2017.
//

#include "cmp_mesh_renderer.h"
#include "cmp_camera.h"
#include <Entity.h>
#include <Renderer.h>
#include <components/cmp_3d.h>
#include <data_ops.h>

sb::cmp_mesh_renderer::cmp_mesh_renderer() : mesh(nullptr), effect(nullptr), Component("Mesh Renderer") {}

void sb::cmp_mesh_renderer::SetMesh(const std::string &path) { mesh = data_ops::GetMesh(path); }

void sb::cmp_mesh_renderer::SetEffect(const std::string &path) { effect = data_ops::GetEffect(path); }

void sb::cmp_mesh_renderer::Render() {
  Component::Render();
  const glm::mat4 mvp = sb::cmp_camera::GetActiveCam().GetVP() * Ent_->GetComponent<sb::cmp_3d>().GetTransform();
  Renderer::Render(mesh, effect, mvp, Renderer::RenderFlags());
}
