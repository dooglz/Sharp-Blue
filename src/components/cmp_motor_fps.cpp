#include "cmp_motor_fps.h"
#include "cmp_3d.h"
#include <Input.h>
#include <glm/gtc/matrix_transform.hpp>

sb::cmp_motor_fps::~cmp_motor_fps() {}

sb::cmp_motor_fps::cmp_motor_fps() : Component("fps_motor") {}

void sb::cmp_motor_fps::Update(double delta) {
  Component::Update(delta);
  const static auto mover = Ent_->GetCompatibleComponent<cmp_3d>();
  glm::dvec3 move;
  if (sb::Input::IsKeyDown(SDLK_w)) {
    move += glm::dvec3(10., 0., 0.);
  }
  if (sb::Input::IsKeyDown(SDLK_s)) {
    move += glm::dvec3(-10., 0., 0.);
  }
  if (sb::Input::IsKeyDown(SDLK_a)) {
    move += glm::dvec3(0., 0., -10.);
  }
  if (sb::Input::IsKeyDown(SDLK_d)) {
    move += glm::dvec3(0., 0., 10.);
  }
  mover->Move(move * delta);
}
