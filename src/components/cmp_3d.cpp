//
// Created by Sam Serrels on 01/04/2017.
//

#include "cmp_3d.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

namespace sb {
cmp_3d::cmp_3d()
    : scale_(glm::dvec3(1.0f)), rotation_(glm::dquat()), position_(glm::dvec3()), changed_(false), Component("3D") {}

cmp_3d::~cmp_3d() {}

void cmp_3d::Update(double delta) {
  transform_ = glm::translate(position_) * mat4_cast(rotation_) * glm::scale(scale_);
  Component::Update(delta);
}

void cmp_3d::Render() { Component::Render(); }

const glm::dvec3 cmp_3d::GetScale() const { return scale_; }

const glm::dvec3 cmp_3d::GetPosition() const { return position_; }

const glm::dvec3 cmp_3d::GetRotationV3() const { return glm::dvec3(); }

const glm::dquat cmp_3d::GetRotation() const { return rotation_; }

const glm::dmat4 cmp_3d::GetTransform() { return transform_; }

const bool cmp_3d::IsVisible() const { return 0; }

void cmp_3d::SetTransform(const glm::dmat4 m4) { transform_ = m4; }

void cmp_3d::SetScale(const glm::dvec3 &v3) { scale_ = v3; }

void cmp_3d::SetPosition(const glm::dvec3 &v3) { position_ = v3; }

void cmp_3d::Move(const glm::dvec3 &v3) { SetPosition(position_ + v3); }

void cmp_3d::SetRotation(const glm::dvec3 &v3) {}

void cmp_3d::SetRotation(const glm::dquat &q) { rotation_ = q; }

void cmp_3d::Rotate(const glm::dvec3 &v3) { SetRotation(rotation_ * glm::dquat(v3)); }
void cmp_3d::Rotate(const glm::dquat &q) { SetRotation(rotation_ * q); }

void cmp_3d::SetVisibility(const bool b) {}

cmp_3d::cmp_3d(glm::dvec3 pos, glm::dvec3 rot, glm::dvec3 scale) : cmp_3d() {
  SetPosition(pos);
  SetRotation(rot);
  SetScale(scale);
}
} // namespace sb