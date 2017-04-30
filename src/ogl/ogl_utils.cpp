#include "ogl_utils.h"
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <map>
#include <iostream>
#define CHECK_GL_ERROR false
namespace ogl {


enum BUFFER_INDEXES {
  // The position data
  POSITION_BUFFER = 0,
  // The colour data
  COLOUR_BUFFER = 1,
  // The surface normals
  NORMAL_BUFFER = 2,
  // The binormals for the surfaces
  BINORMAL_BUFFER = 3,
  // The tangents for the surfaces
  TANGENT_BUFFER = 4,
  // Texture coordinates 0
  TEXTURE_COORDS_0 = 10,
  // Texture coordinates 1
  TEXTURE_COORDS_1 = 11,
  // Texture coordinates 2
  TEXTURE_COORDS_2 = 12,
  // Texture coordinates 3
  TEXTURE_COORDS_3 = 13,
  // Texture coordinates 4
  TEXTURE_COORDS_4 = 14,
  // Texture coordinates 5
  TEXTURE_COORDS_5 = 15
};

struct ogl_mesh {
  // The primitive geometry type used by the geometry
  GLenum type;
  // The OpenGL ID of the vertex array object
  GLuint vao;
  // The OpenGL IDs of the buffers used within the vertex array object
  std::map<GLuint, GLuint> buffers;
  // The OpenGL ID of the index buffer
  GLuint index_buffer;
  // The number of vertices in the geometry
  GLuint vertices;
  // The number of indices in the index buffer
  GLuint indices;
};

// Adds a buffer of vec2 data to the geometry object
bool add_buffer(ogl_mesh &om, const std::vector<glm::vec2> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW);
// Adds a buffer of vec3 data to the geometry object
bool add_buffer(ogl_mesh & om,const std::vector<glm::vec3> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW);
// Adds a buffer of vec4 data to the geometry object
bool add_buffer(ogl_mesh & om,const std::vector<glm::vec4> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW){return false;}

bool add_buffer(ogl_mesh &om, const std::vector<glm::vec2> &buffer, GLuint index, GLenum buffer_type) {
  // Check that index is viable
  assert(index < 16);
  // Check that buffer is not empty
  assert(buffer.size() > 0);
  // Check if geometry initialised
  if (om.vao == 0) {
    // Create the vertex array object
    glGenVertexArrays(1, &om.vao);
    // Check for any OpenGL error
    if (CHECK_GL_ERROR) {
      // Display error
      std::cerr << "ERROR - creating geometry" << std::endl;
      std::cerr << "Could not generate vertex array object" << std::endl;
      // Set vertex array object to 0
      om.vao = 0;
      // Throw exception
      throw std::runtime_error("Error creating vertex array object with OpenGL");
    }
  }
  // If we have no vertices yet, set the vertices to the size of this buffer
  if (om.vertices == 0)
    om.vertices = static_cast<GLuint>(buffer.size());
  // Otherwise ensure that the number of vertices matches
  else if (om.vertices != buffer.size()) {
    std::cerr << "ERROR - adding buffer to geometry object" << std::endl;
    std::cerr << "Buffer does not contain correct amount of vertices" << std::endl;
    return false;
  }
  // Now add buffer to the vertex array object.  Bind the vertex array object
  glBindVertexArray(om.vao);
  // Generate buffer with OpenGL
  GLuint id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  // Set the buffer data
  glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec2), &buffer[0], buffer_type);
  // Set the vertex pointer and enable
  glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(index);
  // Check for OpenGL error
  if (CHECK_GL_ERROR) {
    std::cerr << "ERROR - adding buffer to geometry object" << std::endl;
    std::cerr << "Could not create buffer with OpenGL" << std::endl;
    return false;
  }
  // Add buffer to map
  om.buffers[index] = id;
  return true;
}

// Adds a buffer to the geometry object
bool add_buffer( ogl_mesh & om,const std::vector<glm::vec3> &buffer, GLuint index, GLenum buffer_type) {
  // Check that index is viable
  assert(index < 16);
  // Check that buffer is not empty
  assert(buffer.size() > 0);
  // Check if geometry initialised
  if (om.vao == 0) {
    // Create the vertex array object
    glGenVertexArrays(1, &om.vao);
    // Check for any OpenGL error
    if (CHECK_GL_ERROR) {
      // Display error
      std::cerr << "ERROR - creating geometry" << std::endl;
      std::cerr << "Could not generate vertex array object" << std::endl;
      // Set vertex array object to 0
      om.vao = 0;
      // Throw exception
      throw std::runtime_error("Error creating vertex array object with OpenGL");
    }
  }
  // If we have no vertices yet, set the vertices to the size of this buffer
  if (om.vertices == 0)
    om.vertices = static_cast<GLuint>(buffer.size());
    // Otherwise ensure that the number of vertices matches
  else if (om.vertices != buffer.size()) {
    std::cerr << "ERROR - adding buffer to geometry object" << std::endl;
    std::cerr << "Buffer does not contain correct amount of vertices" << std::endl;
    return false;
  }
  // Now add buffer to the vertex array object.  Bind the vertex array object
  glBindVertexArray(om.vao);
  // Generate buffer with OpenGL
  GLuint id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  // Set the buffer data
  glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(glm::vec3), &buffer[0], buffer_type);
  // Set the vertex pointer and enable
  glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(index);
  // Check for OpenGL error
  if (CHECK_GL_ERROR) {
    std::cerr << "ERROR - adding buffer to geometry object" << std::endl;
    std::cerr << "Could not create buffer with OpenGL" << std::endl;
    return false;
  }
  // Add buffer to map
  om.buffers[index] = id;
  return true;
}

void LoadModel(Mesh *msh) {
  ogl_mesh* om = new ogl_mesh();
  msh->GpuData = om;
  // Add the buffers to the geometry
  add_buffer(*om,msh->positions, BUFFER_INDEXES::POSITION_BUFFER);
  add_buffer(*om,msh->colours, BUFFER_INDEXES::COLOUR_BUFFER);
  if (msh->normals.size() != 0) {
    add_buffer(*om,msh->normals, BUFFER_INDEXES::NORMAL_BUFFER);
    //generate_tb(normals);
  }
  if (msh->tex_coords.size() != 0) {
    add_buffer(*om,msh->tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
  }
  if (msh->indices.size() != 0) {
   // add_index_buffer(om,msh->indices);
  }
}
}