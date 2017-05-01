//
// Created by Sam Serrels on 18/04/2017.
//
#include "Renderer.h"
#include "data_ops.h"
#include "ogl/ogl_utils.h"
#include <memory>
#include <vector>

using namespace std;
namespace sb {
struct Rjob {
  Mesh *mesh;
  Effect *effect;
  const glm::mat4 MVP;
  const Renderer::RenderFlags Flags;
  Rjob(Mesh *md, Effect *eff, const glm::mat4 mvp, const Renderer::RenderFlags fl)
      : mesh(md), effect(eff), MVP(mvp), Flags(fl) {}
};

std::vector<unique_ptr<Rjob>> jobs;

void sb::Renderer::Render(Mesh *mesh, Effect *eff, const glm::mat4 &MVP, const sb::Renderer::RenderFlags &Flags) {
  jobs.push_back(make_unique<Rjob>(mesh, eff, MVP, Flags));
}

void Renderer::AddLight(const sb::Renderer::LightData &ld, const glm::vec3 &position, const glm::quat &rot) {}

void Renderer::Dispatch() {
  // Todo: optimise render queue to mimiizse state change
  for (auto &job : jobs) {
    ogl::Render(job->mesh, job->effect, job->MVP);
  }
  jobs.clear();
}
} // namespace sb