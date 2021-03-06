#pragma once
#include "../Entity.h"
#include <glm/glm.hpp>

namespace sb {
class cmp_motor_fps : public Component {
protected:
  void from_json(const nlohmann::json &j);

public:
  void Update(double delta) override;

  cmp_motor_fps();
  virtual ~cmp_motor_fps();
};
} // namespace sb
