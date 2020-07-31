#version 400 core

in vec4 pass_color;

out vec4 out_Colour;

void main (void) {
  out_Colour = pass_color;
}

