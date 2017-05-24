//
// Created by Sam Serrels on 01/04/2017.
//
#include "cmp_camera.h"
#include "cmp_3d.h"
#include <glm/gtc/matrix_transform.hpp>
sb::cmp_camera *sb::cmp_camera::activeCam_ = nullptr;
void sb::cmp_camera::SetActive() { activeCam_ = this; }

glm::dmat4 sb::cmp_camera::GetVP() const {
  if (activeCam_ == nullptr) {
    // Todo: throw warning/error
    return glm::dmat4();
  }
  return projMat_ * viewMat_;
}

sb::cmp_camera::cmp_camera()
    : projMat_(glm::perspective(1.0472f, (16.0f / 9.0f), 0.01f, 1000.0f)),
      viewMat_(glm::lookAt(glm::vec3(2.0f), glm::vec3(), glm::vec3(0, 1.0f, 0))), Component("camera") {}

sb::cmp_camera::~cmp_camera() {
  if (activeCam_ == this) {
    activeCam_ = nullptr;
  }
  int r = 6;
}

void sb::cmp_camera::from_json(const nlohmann::json &j) {}

sb::cmp_camera &sb::cmp_camera::GetActiveCam() { return *activeCam_; }

void sb::cmp_camera::Update(double delta) {
  Component::Update(delta);
  const sb::cmp_3d &trn(Ent_->GetComponent<sb::cmp_3d>());
  viewMat_ = glm::inverse(trn.GetTransform());
  // viewMat_ = glm::lookAt(trn, trn + glm::vec3(0,0,-1.0f), glm::vec3(0, 1.0f, 0));
}
