//
// Created by Sam Serrels on 01/04/2017.
//

#include "Entity.h"
//#include "game.h"
#include <algorithm>
//#include <glm/gtx/transform.hpp>
namespace sb {
// using namespace glm;
using namespace std;

Component::Component(const string &token) : token_(token) {
  Ent_ = nullptr;
  active_ = false;
}

Component::~Component() {}

bool Component::IsActive() { return active_; }

void Component::SetActive(bool b) { active_ = b; }

void Component::SetParent(Entity *p) { Ent_ = p; }

Entity *Component::GetParent() const { return Ent_; }

//############## Entity ###################

Entity::Entity() {}

Entity::~Entity() {}

const string Entity::GetName() const { return name_; }

void Entity::SetName(string const &name) { name_ = name; }

void Entity::Update(const double delta) {
  for (auto &c : components) {
    c.second->Update(delta);
  }
}

void Entity::Render() {
  for (auto &c : components) {
    c.second->Render();
  }
}
/*
void Entity::RemoveComponent(Component &c) {
  // Todo: Test This
  auto position =
      find_if(components_.begin(), components_.end(), [c](unique_ptr<Component> &p) { return p.get() == &c; });
  if (position != components_.end()) {
    components_.erase(position);
  }
}
*/

} // namespace sb