#pragma once

#include <string>

namespace sb {
class data_ops {
public:
  static void *GetMesh(const std::string& path);
};
}
