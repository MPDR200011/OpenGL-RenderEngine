#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
  glm::vec3 position;
  float pitch;
  float yaw;
  float roll;

public:
  Camera();
  Camera(glm::vec3);

  void setPosition(glm::vec3);
  void move(glm::vec3);

  void rotateX(float);
  void rotateZ(float);
  void rotateY(float);

  glm::mat4 getViewMatrix() const;
};
