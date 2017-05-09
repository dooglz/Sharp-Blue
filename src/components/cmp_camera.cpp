//
// Created by Sam Serrels on 01/04/2017.
//
#include "cmp_camera.h"
#include <glm/gtc/matrix_transform.hpp>
std::shared_ptr<sb::cmp_camera> sb::cmp_camera::activeCam = nullptr;
void sb::cmp_camera::SetActive() { activeCam = std::shared_ptr<cmp_camera>(this); }

glm::dmat4 sb::cmp_camera::GetVP() const {
  if (activeCam == nullptr) {
    // Todo: throw warning/error
    return glm::dmat4();
  }
  return projMat_ * viewMat_;
}

sb::cmp_camera::cmp_camera()
    : projMat_(glm::perspective(1.0472f, (16.0f / 9.0f), 0.01f, 1000.0f)),
      viewMat_(glm::lookAt(glm::vec3(2.0f), glm::vec3(), glm::vec3(0, 1.0f, 0))), Component("camera") {}
