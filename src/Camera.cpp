#include "Camera.hpp"

Camera::Camera() : position(), pitch(), yaw(), roll(){}
Camera::Camera(glm::vec3 pos) : position(pos), pitch(), yaw(), roll() {}

void Camera::setPosition(glm::vec3 position) {
  this->position = position;
}

void Camera::move(glm::vec3 delta) {
  position += delta;
}

void Camera::rotateX(float angle) {
  pitch += angle;
}
void Camera::rotateZ(float angle) {
  roll += angle;
}
void Camera::rotateY(float angle) {
  yaw += angle;
}

glm::mat4 Camera::getViewMatrix() const {
  glm::mat4 view = glm::rotate(glm::identity<glm::mat4>(), pitch, {1.0,0.0,0.0});
  view = glm::rotate(view, yaw, {0.0,1.0,0.0});
  view = glm::rotate(view, roll, {0.0,0.0,1.0});

  view = glm::translate(view, position);

  return glm::inverse(view);
}
