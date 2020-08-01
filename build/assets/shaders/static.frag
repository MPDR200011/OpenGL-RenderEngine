#version 400 core

in vec3 toCam;
in vec3 toLight;
in vec3 passNormal;

out vec4 out_Colour;

void main (void) {
  vec3 lightColor = vec3(1.0, 1.0, 1.0);
  vec4 color = vec4(1.0,0,0,1.0);

  vec3 unitToCam = normalize(toCam);
  vec3 unitToLight = normalize(toLight);
  vec3 unitNormal = normalize(passNormal);

  float brightness = max(dot(unitNormal, unitToLight), 0.5);
  vec3 diffuse =  brightness * lightColor;

  vec3 lightDirection = -unitToLight;
  vec3 reflected = reflect(lightDirection, unitNormal);

  float specular = dot(reflected, unitToCam);
  specular = max(specular, 0);
 
  float dampedFactor = pow(specular, 100);
  vec3 finalSpecular = dampedFactor * 1 * lightColor;

  out_Colour = vec4(diffuse, 1.0) * color + vec4(finalSpecular, 1.0);

}

