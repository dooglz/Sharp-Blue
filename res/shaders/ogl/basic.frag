#version 410 core

// Incoming vertex colour
layout(location = 0) in vec4 frag_colour;

// Outgoing pixel colour
out vec4 out_colour;

void main() {
  // Simply set outgoing colour
  out_colour = frag_colour;
  // out_colour = vec4(1.0,0,0,1.0);
}