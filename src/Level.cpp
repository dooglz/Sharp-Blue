//
// Created by Sam Serrels on 01/04/2017.
//

#include "Level.h"
namespace sb {

void Level::AddToScene(std::unique_ptr<Entity> ent) { scenelist.push_back(move(ent)); }

std::vector<std::unique_ptr<Entity>> *Level::GetSceneList() { return &scenelist; }

const Entity *const Level::GetEnt(const std::string &name) const {
  for (auto &e : scenelist) {
    if (e->GetName() == name) {
      return e.get();
    }
  }
}
} // namespace sb