#pragma once
#include "Entity.h"

namespace sb {
void LoadLevel();
class Level {
protected:
  void (*gameUpdateFunc)(double);
  void (*gameLoadInFunc)(double);
  void (*gameLoadOutFunc)(double);
  std::vector<std::unique_ptr<Entity>> scenelist;

public:
  void AddToScene(std::unique_ptr<Entity> ent);
  std::vector<std::unique_ptr<Entity>> *GetSceneList();
};
}