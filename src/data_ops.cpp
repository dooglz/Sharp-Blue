//
// Created by Sam Serrels on 18/04/2017.
//

#include "data_ops.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <GL/glew.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <ogl/ogl_utils.h>
namespace sb {
using namespace std;
inline bool check_file_exists(const std::string &filename) {
  std::ifstream file(filename);
  return file.good();
}

const string pathMangle(const string &path) { return path; }

Mesh *data_ops::GetMesh(const std::string &p) {
  // return nullptr;
  const string path = pathMangle(p);

  // Check that file exists

  if (!check_file_exists(path)) {
    // Failed to read file.  Display error
    std::cerr << "ERROR - could not load model file " << path << std::endl;
    std::cerr << "File Does Not Exist" << std::endl;
    // Throw exception
    throw std::runtime_error("Error loading model file");
  }

  // Create model importer
  Assimp::Importer model_importer;
  // Read in the model data
  auto sc = model_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                              aiProcess_ValidateDataStructure | aiProcess_FindInvalidData);
  // Check that data has been read in correctly
  if (!sc) {
    // Display error
    std::cerr << "ERROR - loading geometry " << path << std::endl;
    std::cerr << model_importer.GetErrorString() << std::endl;
    // Throw exception
    throw std::runtime_error("Error reading in model file");
  }
  // TODO - read in multiple texture coordinates
  // TODO - mesh hierarchy?
  // TODO - bones
  // TODO - multiple colour values
  Mesh *ret = new Mesh();

  unsigned int vertex_begin = 0;
  // Iterate through each sub-mesh in the model
  for (unsigned int n = 0; n < sc->mNumMeshes; ++n) {
    // Get the sub-mesh
    auto mesh = sc->mMeshes[n];
    // Iterate through all the vertices in the sub-mesh
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
      // Get position vertex
      auto pos = mesh->mVertices[i];
      // Add to positions data
      ret->positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
    }
    // If we have colour data then iterate through them
    if (mesh->HasVertexColors(0))
      // Iterate through colour data
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        // Get the colour data from the mesh
        auto col = mesh->mColors[0][i];
        // Add to colour data vector
        ret->colours.push_back(glm::vec4(col.r, col.g, col.b, col.a));
      }
    // Otherwise just push back grey
    else
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        ret->colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    // If we have normals, then add to normal data
    if (mesh->HasNormals())
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        auto norm = mesh->mNormals[i];
        ret->normals.push_back(glm::vec3(norm.x, norm.y, norm.z));
      }
    // If we have texture coordinates then add to texture coordinate data
    if (mesh->HasTextureCoords(0))
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        auto tex_coord = mesh->mTextureCoords[0][i];
        ret->tex_coords.push_back(glm::vec2(tex_coord.x, tex_coord.y));
      }
    // If we have face information, then add to index buffer
    if (mesh->HasFaces())
      for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
        auto face = mesh->mFaces[f];
        for (auto i = 0; i < 3; ++i)
          ret->indices.push_back(vertex_begin + face.mIndices[i]);
      }
    vertex_begin += mesh->mNumVertices;
  }

  // Calculate the minimal and maximal
  ret->min = ret->positions[0];
  ret->max = ret->positions[0];
  for (auto &v : ret->positions) {
    ret->min = glm::min(ret->min, v);
    ret->max = glm::max(ret->max, v);
  }

  // hand over to implemntation
  ogl::LoadModel(ret);

  // Log success
  std::clog << "LOG - geometry " << path << " loaded "
            << (ret->normals.size() ? "With normals & " : "With no normals & ")
            << (ret->tex_coords.size() ? "With UVs" : "With no UVs") << std::endl;

  return ret;
}
}