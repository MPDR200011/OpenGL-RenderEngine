#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec4 pass_color;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;

void main(void) {
  vec3 lightPosition = vec3(1,1,1);

  vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
  vec4 posRelToCam = viewMatrix * worldPosition;

  //Position
  gl_Position =  posRelToCam;
  pass_color = normalize(vec4(normal, 1.0));
}

