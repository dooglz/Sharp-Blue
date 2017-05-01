//
// Created by Sam Serrels on 18/04/2017.
//

#include "data_ops.h"
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <ogl/ogl_utils.h>
#include <sstream>
namespace sb {
using namespace std;
using namespace glm;
const static glm::vec4 coloursA[3] = {vec4(0.65f, 0.81f, 0.89f, 1.0f), vec4(0.12f, 0.47f, 0.71f, 1.0f),
                                      vec4(0.7f, 0.87f, 0.54f, 1.0f)};
const static glm::vec4 coloursB[3] = {vec4(0.11f, 0.62f, 0.47f, 1.0f), vec4(0.85f, 0.37f, 0.01f, 1.0f),
                                      vec4(0.46f, 0.44f, 0.7f, 1.0f)};
const static glm::vec4 coloursC[3] = {vec4(0.4f, 0.76f, 0.65f, 1.0f), vec4(0.99f, 0.55f, 0.38f, 1.0f),
                                      vec4(0.55f, 0.63f, 0.8f, 1.0f)};
const static glm::vec4 coloursD[3] = {vec4(0.533f, 0.898f, 0.231, 1.0f), vec4(1.0f, 0.698f, 0.259, 1.0f),
                                      vec4(0.412f, 0.227f, 0.702f, 1.0f)};
inline bool check_file_exists(const std::string &filename) {
  std::ifstream file(filename);
  return file.good();
}

bool Findfile(string &path) {
  static const std::string filedirs[] = {"", "res/", "res/mdl/", "res/fonts/", "res/sound/", "res/shaders/ogl/"};
  for (const auto s : filedirs) {
    ifstream inFile((s + path).c_str(), ifstream::in);
    if (inFile.good()) {
      path = s + path;
      return true;
    }
  }
  return false;
}

bool read_file(const std::string &filename, std::string &content) {
  // Create filestream
  std::ifstream file(filename, std::ios_base::in);
  // Check that file exists.  If not, return false
  if (file.bad())
    return false;

  // File is good.  Read contents
  std::stringstream buffer;
  buffer << file.rdbuf();

  // Get contents from the file
  content = buffer.str();

  // Close file and return true
  file.close();
  return true;
}

Mesh *data_ops::GetMesh(const std::string &file) {
  string path = file;
  if (!Findfile(path)) {
    std::cerr << "ERROR - could not find file " << path << std::endl;
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
        ret->colours.push_back(coloursD[i % 3]);
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

Effect *data_ops::GetEffect(const std::string &path) {
  string vert_path = path + ".vert";
  string frag_path = path + ".frag";
  string geom_path = path + ".geom";
  string vert_file, frag_file, geom_file;

  if (!Findfile(vert_path) || !read_file(vert_path, vert_file)) {
    throw std::runtime_error("Error loading vert");
  }

  if (!Findfile(frag_path) || !read_file(frag_path, frag_file)) {
    throw std::runtime_error("Error loading vert");
  }

  auto e = new Effect();
  e->name = path;
  e->has_geometry = (Findfile(geom_path) && read_file(geom_path, geom_file));

  ogl::LoadEffect(e, vert_file, frag_file, geom_file);

  return e;
}
} // namespace sb