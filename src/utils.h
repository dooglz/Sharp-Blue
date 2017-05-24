#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

inline glm::vec2 SVecToGVec2(const std::vector<float> &const v) { return glm::vec2(v[0], v[1]); }
inline glm::vec3 SVecToGVec3(const std::vector<float> &const v) { return glm::vec3(v[0], v[1], v[2]); }
inline glm::vec4 SVecToGVec4(const std::vector<float> &const v) { return glm::vec4(v[0], v[1], v[2], v[3]); }
inline glm::dvec2 SVecToGVec2(const std::vector<double> &const v) { return glm::dvec2(v[0], v[1]); }
inline glm::dvec3 SVecToGVec3(const std::vector<double> &const v) { return glm::dvec3(v[0], v[1], v[2]); }
inline glm::dvec4 SVecToGVec4(const std::vector<double> &const v) { return glm::dvec4(v[0], v[1], v[2], v[3]); }