//
// Created by Sam Serrels on 01/04/2017.
//

#ifndef SHARP_BLUE_CMP_3D_H
#define SHARP_BLUE_CMP_3D_H

#include "../Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace sb {
  class cmp_3d : public Component {
  protected:
    bool changed_;
    glm::dvec3 scale_;
    glm::dvec3 position_;
    glm::dquat rotation_;
    glm::dmat4 transform_;

  public:
    cmp_3d();

    ~cmp_3d();

    void Update(double delta);

    void Render();

    const glm::dvec3 GetScale() const;

    const glm::dvec3 GetPosition() const;

    const glm::dvec3 GetRotationV3() const;

    const glm::dquat GetRotation() const;

    const glm::dmat4 GetTranform();

    const bool IsVisible() const;

    void SetTransform(const glm::dmat4 m4);

    void SetScale(const glm::dvec3 &v3);

    void SetPosition(const glm::dvec3 &v3);

    void SetRotation(const glm::dvec3 &v3);

    void SetRotation(const glm::dquat &q);

    void SetVisibility(const bool b);
  };
}

#endif // SHARP_BLUE_CMP_3D_H
