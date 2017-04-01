//
// Created by Sam Serrels on 01/04/2017.
//

#include "cmp_3d.h"

namespace sb {
cmp_3d::cmp_3d() : Component("3D") {}

cmp_3d::~cmp_3d() {}

void cmp_3d::Update(double delta) { Component::Update(delta); }

void cmp_3d::Render() { Component::Render(); }

const glm::dvec3 cmp_3d::GetScale() const { return glm::dvec3(); }

const glm::dvec3 cmp_3d::GetPosition() const { return glm::dvec3(); }

const glm::dvec3 cmp_3d::GetRotationV3() const { return glm::dvec3(); }

const glm::dquat cmp_3d::GetRotation() const { return glm::dquat(); }

const glm::dmat4 cmp_3d::GetTranform() { return glm::dmat4(); }

const bool cmp_3d::IsVisible() const { return 0; }

void cmp_3d::SetTransform(const glm::dmat4 m4) {}

void cmp_3d::SetScale(const glm::dvec3 &v3) {}

void cmp_3d::SetPosition(const glm::dvec3 &v3) {}

void cmp_3d::SetRotation(const glm::dvec3 &v3) {}

void cmp_3d::SetRotation(const glm::dquat &q) {}

void cmp_3d::SetVisibility(const bool b) {}
}