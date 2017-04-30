//
// Created by Sam Serrels on 18/04/2017.
//

#include <fstream>
#include <iostream>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "data_ops.h"
#include "assimp/importer.hpp"
namespace sb {
using namespace std;
inline bool check_file_exists(const std::string &filename) {
  std::ifstream file(filename);
  return file.good();
}

const string pathMangle(const string& path){
  return path;
}

void *data_ops::GetMesh(const std::string& p) {
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
  auto sc = model_importer.ReadFile(path,
                                    aiProcess_Triangulate | aiProcess_GenSmoothNormals |
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
  // Declare vectors to store data
  std::vector<glm::vec3> positions;
  std::vector<glm::vec4> colours;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> tex_coords;
  std::vector<GLuint> indices;
  
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
      positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
    }
    // If we have colour data then iterate through them
    if (mesh->HasVertexColors(0))
      // Iterate through colour data
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        // Get the colour data from the mesh
        auto col = mesh->mColors[0][i];
        // Add to colour data vector
        colours.push_back(glm::vec4(col.r, col.g, col.b, col.a));
      }
      // Otherwise just push back grey
    else
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        colours.push_back(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
    // If we have normals, then add to normal data
    if (mesh->HasNormals())
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        auto norm = mesh->mNormals[i];
        normals.push_back(glm::vec3(norm.x, norm.y, norm.z));
      }
    // If we have texture coordinates then add to texture coordinate data
    if (mesh->HasTextureCoords(0))
      for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        auto tex_coord = mesh->mTextureCoords[0][i];
        tex_coords.push_back(glm::vec2(tex_coord.x, tex_coord.y));
      }
    // If we have face information, then add to index buffer
    if (mesh->HasFaces())
      for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
        auto face = mesh->mFaces[f];
        for (auto i = 0; i < 3; ++i)
          indices.push_back(vertex_begin + face.mIndices[i]);
      }
    vertex_begin += mesh->mNumVertices;
  }

  // Calculate the minimal and maximal
  for (auto &v : positions) {
    _minimal = glm::min(_minimal, v);
    _maximal = glm::max(_maximal, v);
  }

  // Add the buffers to the geometry
  add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
  add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
  if (normals.size() != 0) {
    add_buffer(normals, BUFFER_INDEXES::NORMAL_BUFFER);
    generate_tb(normals);
  }
  if (tex_coords.size() != 0) {
    add_buffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
  }
  if (indices.size() != 0) {
    add_index_buffer(indices);
  }
  // Log success
  std::clog << "LOG - geometry " << filename << " loaded "
            << (normals.size() ? "With normals & " : "With no normals & ")
            << (tex_coords.size() ? "With UVs" : "With no UVs") << std::endl;


}
}