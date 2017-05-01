#pragma once
#include <Entity.h>

namespace sb {
class cmp_light : public Component {
public:
  cmp_light();
  void Render() override;
};
} // namespace sb
