#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec3 toCam;
out vec3 toLight;
out vec3 passNormal;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void) {
  vec3 lightPosition = vec3(0,0,2);

  vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
  vec4 posRelToCam = viewMatrix * worldPosition;

  //Position
  gl_Position =  projectionMatrix * posRelToCam;

  passNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
  toCam = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;
  toLight = lightPosition - worldPosition.xyz;
}

