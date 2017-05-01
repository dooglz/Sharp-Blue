#include "ogl_utils.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)
namespace sb {
namespace ogl {

inline bool get_GL_error(int line, const std::string &file) {
  // Get the current error
  GLenum error = glGetError();
  // If there is an error display message
  if (error) {
    // Display error
    std::cerr << "OpenGL Error: " << error << std::endl;
    std::cerr << "At line " << line << " in file " << file << std::endl;
    return true;
  }
  return false;
}

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
  bool has_indices;
  // The number of vertices in the geometry
  // GLuint vertices;
  // The number of indices in the index buffer
  GLuint indice_count;
  GLuint vertex_count;
};

struct ogl_shader_program {
  GLuint vert;
  GLuint frag;
  GLuint geom;
  GLuint program;
};

bool Setup_Vao(ogl_mesh &om) {
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
    return false;
  }
  return true;
}

bool add_buffer(ogl_mesh &om, const void *data, GLuint stride, GLuint size, GLuint index, GLenum buffer_type) {
  // Check that index is viable
  assert(index < 16);
  // Check that buffer is not empty
  assert(size > 0);
  // Check if geometry initialised
  if (om.vao == 0) {
    Setup_Vao(om);
  }
  // Now add buffer to the vertex array object.  Bind the vertex array object
  glBindVertexArray(om.vao);
  // Generate buffer with OpenGL
  GLuint id;
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  // Set the buffer data
  glBufferData(GL_ARRAY_BUFFER, size, data, buffer_type);
  // Set the vertex pointer and enable
  glVertexAttribPointer(index, stride, GL_FLOAT, GL_FALSE, 0, 0);
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

bool add_index_buffer(ogl_mesh &om, const std::vector<GLuint> &buffer) {
  // Check that buffer is not empty
  assert(buffer.size() > 0);
  // Check if vertex array object is valid
  assert(om.vao != 0);
  // Set indices to buffer size
  om.indice_count = static_cast<GLuint>(buffer.size());
  // Bind vertex array object
  glBindVertexArray(om.vao);
  // Add buffer
  glGenBuffers(1, &om.index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, om.index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), &buffer[0], GL_STATIC_DRAW);
  // Check for error
  if (CHECK_GL_ERROR) {
    std::cerr << "Error - adding index buffer to geometry object" << std::endl;
    std::cerr << "Could not create buffer with OpenGL" << std::endl;
    return false;
  }
  return true;
}

bool add_buffer(ogl_mesh &om, const std::vector<glm::vec2> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW) {
  return add_buffer(om, &buffer[0], 2, static_cast<GLuint>(buffer.size() * sizeof(glm::vec2)), index, buffer_type);
}
bool add_buffer(ogl_mesh &om, const std::vector<glm::vec3> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW) {
  return add_buffer(om, &buffer[0], 3, static_cast<GLuint>(buffer.size() * sizeof(glm::vec3)), index, buffer_type);
}
bool add_buffer(ogl_mesh &om, const std::vector<glm::vec4> &buffer, GLuint index, GLenum buffer_type = GL_STATIC_DRAW) {
  return add_buffer(om, &buffer[0], 4, static_cast<GLuint>(buffer.size() * sizeof(glm::vec4)), index, buffer_type);
}

void LoadModel(Mesh *msh) {
  ogl_mesh *om = new ogl_mesh();
  msh->GpuData = om;
  om->type = GL_TRIANGLES;
  // Add the buffers to the geometry
  add_buffer(*om, msh->positions, BUFFER_INDEXES::POSITION_BUFFER);
  add_buffer(*om, msh->colours, BUFFER_INDEXES::COLOUR_BUFFER);
  if (msh->normals.size() != 0) {
    add_buffer(*om, msh->normals, BUFFER_INDEXES::NORMAL_BUFFER);
    // generate_tb(normals);
  }
  if (msh->tex_coords.size() != 0) {
    add_buffer(*om, msh->tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
  }
  if (msh->indices.size() != 0) {
    add_index_buffer(*om, msh->indices);
    om->has_indices = true;
  } else {
    om->vertex_count = msh->positions.size();
  }
}

void LoadEffect(Effect *eff, const std::string &vert, const std::string &frag, const std::string &geom) {
  // Create shader with OpenGL
  GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
  // Check if error
  if (CHECK_GL_ERROR) {
    std::cerr << "ERROR - loading shader " << eff->name << std::endl;
    std::cerr << "Could not create shader object with OpenGL" << std::endl;
    throw std::runtime_error("Error adding shader to effect");
  }

  auto *contents = vert.c_str();
  glShaderSource(vertID, 1, &contents, 0);
  contents = frag.c_str();
  glShaderSource(fragID, 1, &contents, 0);

  // Todo: Geom shader
  GLuint ids[2] = {vertID, fragID};
  for (auto &id : ids) {
    // Compile
    glCompileShader(id);
    // Check if error
    if (CHECK_GL_ERROR) {
      // Display error,Throw exception, Todo: is this redundant?
      std::cerr << "ERROR - could not compile file, shader " << eff->name << std::endl;
      throw std::runtime_error("Error adding shader to effect");
      return;
    }
    // We have tried to compile the shader.  Now check if compilation was successful.
    GLint compiled;
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &compiled);
    CHECK_GL_ERROR; // Not considered fatal here
    if (!compiled) {
      // Shader not compiled.  Get log and display
      GLsizei length;
      glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &length);
      // Create vector to store log file
      std::vector<char> log(length);
      // Get the log
      glGetShaderInfoLog(id, length, &length, &log[0]);
      // Display error
      std::cerr << "ERROR - could not compile shader " << eff->name << std::endl;
      std::cerr << &log[0] << std::endl;
      CHECK_GL_ERROR; // Not considered fatal here
      // Remove shader object from OpenGL
      glDeleteShader(id);
      // Throw exception
      throw std::runtime_error("Error adding shader to effect");
      return;
    }
  }
  ogl_shader_program *prog = new ogl_shader_program();
  prog->frag = fragID;
  prog->vert = vertID;
  prog->program = glCreateProgram();

  if (CHECK_GL_ERROR) {
    std::cerr << "ERROR - building effect" << std::endl;
    std::cerr << "Could not create program object with OpenGL" << std::endl;
    throw std::runtime_error("Error creating effect with OpenGL");
  }

  for (auto &id : ids) {
    // Shader has been loaded.  Add to effect
    glAttachShader(prog->program, id);
    // Check if error
    if (CHECK_GL_ERROR) {
      // Display error
      std::cerr << "ERROR - adding shader to effect" << std::endl;
      std::cerr << "Problem attaching shader to program" << std::endl;
      // Throw exception
      throw std::runtime_error("Error adding shader to effect");
    }
  }

  // Attempt to link program
  glLinkProgram(prog->program);
  // Check if error
  if (CHECK_GL_ERROR) {
    // Display error
    std::cerr << "ERROR - building effect " << std::endl;
    std::cerr << "Problem linking program" << std::endl;
    // Detach and delete shaders
    /*for (auto &s : _shaders) {
      glDetachShader(_program, s);
      glDeleteShader(s);
    }*/
    // Delete program
    glDeleteProgram(prog->program);
    // Throw exception
    throw std::runtime_error("Error building effect");
  }

  // Check if linked successfully
  // Get link status
  GLint linked;
  glGetProgramiv(prog->program, GL_LINK_STATUS, &linked);
  // Check if linked OK
  if (!linked) {
    // Program did not link.  Get info log and display error
    GLsizei length;
    glGetProgramiv(prog->program, GL_INFO_LOG_LENGTH, &length);
    // Allocate buffer
    std::vector<char> log(length);
    // Get info log
    glGetProgramInfoLog(prog->program, length, &length, &log[0]);
    // Display error
    std::cerr << "ERROR - building effect" << std::endl;
    std::cerr << "Problem linking program" << std::endl;
    std::cerr << &log[0] << std::endl;
    // Detach shaders
    /* for (auto &s : _shaders) {
      glDetachShader(_program, s);
      glDeleteShader(s);
    }*/
    // Delete program
    glDeleteProgram(prog->program);
    // Throw exception
    throw std::runtime_error("Error building effect");
  }

  eff->GpuData = prog;
  // Effect built sucessfully.  Log
  std::clog << "LOG - effect:" << eff->name << " built" << std::endl;
}

void Render(Mesh *msh, Effect *eff, glm::mat4 MVP) {
  glm::mat4 proj = glm::perspective(1.0472f, (16.0f / 9.0f), 2.414f, 1000.0f);
  glm::mat4 view = glm::lookAt(glm::vec3(2.0f), glm::vec3(), glm::vec3(0, 1.0f, 0));
  MVP = proj * view * MVP;
  ogl_mesh *om = (ogl_mesh *)msh->GpuData;
  ogl_shader_program *sp = (ogl_shader_program *)eff->GpuData;

  glUseProgram(sp->program);
  auto loc = glGetUniformLocation(sp->program, "MVP");
  glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(MVP));

  // Bind the vertex array object for the
  glBindVertexArray(om->vao);
  // Check for any OpenGL errors
  if (CHECK_GL_ERROR) {
    // Display error
    std::cerr << "ERROR - rendering geometry" << std::endl;
    std::cerr << "Could not bind vertex array object" << std::endl;
    // Throw exception
    throw std::runtime_error("Error rendering geometry");
  }
  // If there is an index buffer then use to render
  if (om->has_indices) {
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, om->index_buffer);
    // Check for error
    if (CHECK_GL_ERROR) {
      std::cerr << "ERROR - rendering geometry" << std::endl;
      std::cerr << "Could not bind index buffer" << std::endl;
      // Throw exception
      throw std::runtime_error("Error rendering geometry");
    }
    // Draw elements
    glDrawElements(om->type, om->indice_count, GL_UNSIGNED_INT, nullptr);
    // Check for error
    if (CHECK_GL_ERROR) {
      // Display error
      std::cerr << "ERROR - rendering geometry" << std::endl;
      std::cerr << "Could not draw elements from indices" << std::endl;
      // Throw exception
      throw std::runtime_error("Error rendering geometry");
    }
  } else {
    // Draw arrays
    glDrawArrays(om->type, 0, om->vertex_count);
    // Check for error
    if (CHECK_GL_ERROR) {
      std::cerr << "ERROR - rendering geometry" << std::endl;
      std::cerr << "Could not draw arrays" << std::endl;
      // Throw exception
      throw std::runtime_error("Error rendering geometry");
    }
  }
}
} // namespace ogl
} // namespace sb