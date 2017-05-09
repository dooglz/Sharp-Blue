#pragma once
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

namespace sb {

class Entity;

class Component {
protected:
  Entity *Ent_;
  bool active_;

public:
  std::string token_;
  explicit Component(const std::string &token);
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

  template <typename T> T &GetComponent() const noexcept {
    return *static_cast<T *>(components.at(std::type_index(typeid(T))).get());
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