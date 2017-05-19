#pragma once
#include "../Entity.h"
#include <glm/glm.hpp>

namespace sb {
class cmp_camera : public Component {
protected:
  glm::dmat4 projMat_;
  glm::dmat4 viewMat_;
  static cmp_camera *activeCam_;

public:
  static cmp_camera &GetActiveCam();
  void SetActive();
  glm::dmat4 GetVP() const;
  cmp_camera();

  void Update(double delta) override;

  virtual ~cmp_camera();
};
} // namespace sb
