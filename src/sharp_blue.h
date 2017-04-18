#pragma once
#include "Level.h"
#include <memory>

namespace sb {
void version();
bool init();
void Start();
void SetTickFunc(void (*gt)(double));
void SetStartupFunc(void (*func)());
std::shared_ptr<sb::Level> GetLevel();
}
