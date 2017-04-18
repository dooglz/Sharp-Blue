//
// Created by Sam Serrels on 01/04/2017.
//

#include "cmp_light.h"
#include <Renderer.h>
#include <glm/gtx/quaternion.hpp>

sb::cmp_light::cmp_light() : Component("Light") {}

void sb::cmp_light::Render() {
  Component::Render();
  Renderer::AddLight(Renderer::LightData(), glm::vec3(), glm::quat());
}
