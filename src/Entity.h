#pragma once
#include "json.hpp"
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>
using json = nlohmann::json;

namespace sb {

class Entity;

class Component {
protected:
  Entity *Ent_;
  bool active_;
  Component() = delete;
  Component(const Component &obj) = delete;

public:
  virtual void from_json(const json &j) = 0;
  std::string token_;
  explicit Component(const std::string &token);
  // virtual Component(const json &j) = 0;
  static Component *MakeGeneric(const json &j);

  template <typename T> static T *MakeRaw(const json &j) { return static_cast<T *>(MakeGeneric(j)); }

  template <typename T> static std::unique_ptr<T> MakeUnique(const json &j) {
    return std::unique_ptr<T>(static_cast<T *>(MakeGeneric(j)));
  }

  virtual ~Component();
  virtual void Update(double delta){};
  virtual void Render(){};
  bool IsActive();
  void SetActive(bool b);
  virtual void SetParent(Entity *p);
  Entity *GetParent() const;
};

class Entity {
protected:
  std::string name_;
  using my_map = std::map<std::type_index, std::unique_ptr<Component>>;
  my_map components;

public:
  Entity();
  ~Entity();

  const std::string GetName() const;
  void SetName(std::string const &name);
  virtual void Update(const double delta);
  virtual void Render();

  template <typename T> T &GetComponent() const {
    my_map::const_iterator iter = components.find(std::type_index(typeid(T)));

    if (iter != components.end()) {
      return *static_cast<T *>(iter->second.get());
    }
    throw;
  }

  template <typename T> void AddComponent(std::unique_ptr<T> component) noexcept {
    Component *a = component.get();
    a->SetParent(this);
    components[std::type_index(typeid(T))] = std::move(component);
  }

  // void RemoveComponent(Component &c);

  // Will return a T component, or anything derived from a T component.
  template <typename T> T *const GetCompatibleComponent() {
    for (auto &c : components) {
      auto dd = dynamic_cast<T *>(&(*c.second));
      if (dd) {
        return dd;
      }
    }
    return NULL;
  }
};
} // namespace sb