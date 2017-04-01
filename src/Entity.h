//
// Created by Sam Serrels on 01/04/2017.
//

#ifndef SHARP_BLUE_ENTITY_H
#define SHARP_BLUE_ENTITY_H
#include <string>
#include <vector>

namespace sb {
class Entity;

class Component {
protected:
  Entity *Ent_;
  bool active_;

public:
  std::string token_;
  Component(const std::string &token);
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
  std::vector<std::unique_ptr<Component>> components_;

public:
  Entity();
  ~Entity();

  const std::string GetName() const;
  void SetName(std::string const &name);
  virtual void Update(const double delta);
  virtual void Render();
  void AddComponent(std::unique_ptr<Component> &c);
  void RemoveComponent(Component &c);
  const std::vector<std::unique_ptr<Component>> *GetComponents() const;
  std::vector<Component *> GetComponents(std::string const &name) const;

  template <typename T> T *const getComponent() {
    for (size_t i = 0; i < components_.size(); i++) {
      if (&typeid(*components_[i]) == &typeid(T)) {
        return static_cast<T *>(&*components_[i]);
      }
    }
    return NULL;
  }

  // Will return a T component, or anything derived from a T component.
  template <typename T> T *const getCompatibleComponent() {
    for (size_t i = 0; i < components_.size(); i++) {
      auto dd = dynamic_cast<T *>(&*components_[i]);
      if (dd) {
        return dd;
      }
    }
    return NULL;
  }
};
}
#endif // SHARP_BLUE_ENTITY_H
