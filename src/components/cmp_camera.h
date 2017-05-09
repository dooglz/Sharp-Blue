#pragma once
#include "../Entity.h"
#include <glm/glm.hpp>

namespace sb {
class cmp_camera : public Component {
protected:
  glm::dmat4 projMat_;
  glm::dmat4 viewMat_;

public:
  static std::shared_ptr<cmp_camera> activeCam;
  void SetActive();
  glm::dmat4 GetVP() const;
  cmp_camera();
};
} // namespace sb
