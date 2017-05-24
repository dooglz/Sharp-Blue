#include "cmp_motor_fps.h"
#include "cmp_3d.h"
#include <Input.h>
#include <glm/gtc/matrix_inverse.inl>
#include <glm/gtc/matrix_transform.hpp>

sb::cmp_motor_fps::~cmp_motor_fps() {}

sb::cmp_motor_fps::cmp_motor_fps() : Component("fps_motor") {}

void sb::cmp_motor_fps::from_json(const nlohmann::json & j)
{
}

void sb::cmp_motor_fps::Update(double delta) {
  Component::Update(delta);
  const static auto mover = Ent_->GetCompatibleComponent<cmp_3d>();
  const glm::dvec3 UP = glm::dvec3(0, 1.0, 0);
  const glm::dvec3 RIGHT = glm::dvec3(1.0, 0, 0);
  const glm::dvec3 FORWARD = glm::dvec3(0, 0, -1.0);

  glm::dvec3 move;
  glm::dquat rot;
  if (sb::Input::IsKeyDown(SDLK_w)) {
    move += glm::dvec3(0., 0., -10.);
  }
  if (sb::Input::IsKeyDown(SDLK_s)) {
    move += glm::dvec3(0., 0., 10.);
  }
  if (sb::Input::IsKeyDown(SDLK_a)) {
    move += glm::dvec3(-10., 0., 0.);
  }
  if (sb::Input::IsKeyDown(SDLK_d)) {
    move += glm::dvec3(10., 0., 0.);
  }
  if (sb::Input::IsKeyDown(SDLK_q)) {
    move += glm::dvec3(0., -10., 0);
  }
  if (sb::Input::IsKeyDown(SDLK_e)) {
    move += glm::dvec3(0., 10., 0);
  }

  // pitch
  if (sb::Input::IsKeyDown(SDLK_r)) {
    rot *= glm::quat(glm::vec3(0.5 * delta, 0, 0));
  }
  if (sb::Input::IsKeyDown(SDLK_f)) {
    rot *= glm::quat(glm::vec3(-0.5 * delta, 0, 0));
  }
  if (sb::Input::IsKeyDown(SDLK_t)) {
    rot *= glm::quat(glm::vec3(0, 0.5 * delta, 0));
  }
  if (sb::Input::IsKeyDown(SDLK_g)) {
    rot *= glm::quat(glm::vec3(0, -0.5 * delta, 0));
  }

  mover->SetRotation(glm::normalize(rot * mover->GetRotation()));
  mover->Move(mover->GetRotation() * move * delta);

  if (sb::Input::IsKeyDown(SDLK_z)) {
    mover->SetRotation(glm::dquat());
  }
}
