#pragma once
#include <Entity.h>

namespace sb {
class cmp_light : public Component {
protected:
  void from_json(const nlohmann::json &j);

public:
  cmp_light();
  void Render() override;
};
} // namespace sb
