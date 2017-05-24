//
// Created by Sam Serrels on 01/04/2017.
//

#include "Entity.h"
//#include "game.h"
#include "components/cmp_3d.h"
#include "components/cmp_camera.h"
#include "components/cmp_light.h"
#include "components/cmp_mesh_renderer.h"
#include "components/cmp_motor_fps.h"
#include <algorithm>
#include <iostream>
//#include <glm/gtx/transform.hpp>
namespace sb {
// using namespace glm;
using namespace std;

Component::Component(const string &token) : token_(token) {
  Ent_ = nullptr;
  active_ = false;
}

Component *Component::MakeGeneric(const json &j) {
  const string ctype = j.at("component_type").get<string>();
  Component *cmp;
  if (ctype == "3D") {
    cmp = new cmp_3d();
  } else if (ctype == "camera") {
    cmp = new cmp_camera();
  } else if (ctype == "Light") {
    cmp = new cmp_light();
  } else if (ctype == "Mesh_Renderer") {
    cmp = new cmp_mesh_renderer();
  } else if (ctype == "fps_motor") {
    cmp = new cmp_motor_fps();
  } else {
    cmp = nullptr;
  }
  cmp->from_json(j);

  return cmp;
}

/*
void Component::from_json(const nlohmann::json & j, Component & c)
{
  const string ctype = j.at("component_type").get<string>();
  if (ctype)
}
*/

Component::~Component() {
  cout << "Goodbye from Component: " << token_ << endl;
  Ent_ = nullptr;
  active_ = false;
  token_.clear();
}

bool Component::IsActive() { return active_; }

void Component::SetActive(bool b) { active_ = b; }

void Component::SetParent(Entity *p) { Ent_ = p; }

Entity *Component::GetParent() const { return Ent_; }

//############## Entity ###################

Entity::Entity() { components.clear(); }

Entity::~Entity() {
  components.clear();
  cout << "Goodbye from Entity: " << name_ << endl;
}

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