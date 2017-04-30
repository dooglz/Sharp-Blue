//
// Created by Sam Serrels on 18/04/2017.
//
#include <vector>
#include <memory>
#include "Renderer.h"

using namespace std;

struct Rjob{
  void *MeshData;
  const glm::mat4 MVP;
  const sb::Renderer::RenderFlags Flags;
};

//std::vector<unique_ptr<RJob>> jobs;

void sb::Renderer::Render(void *MeshData, const glm::mat4 &MVP, const sb::Renderer::RenderFlags &Flags) {
 // jobs.push_back(make_unique<Rjob>({MeshData,MVP,Flags}));

}

void sb::Renderer::AddLight(const sb::Renderer::LightData &ld, const glm::vec3 &position, const glm::quat &rot) {}


void sb::Renderer::Dispatch(){


}