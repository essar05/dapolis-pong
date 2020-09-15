#include "Ball.h"
#include <Ess3D/input/InputManager.h>

Ball::Ball() = default;
Ball::Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Ball::~Ball() = default;

bool Ball::onUpdate(float deltaTime) {
  _position += _velocity * deltaTime;

  return true;
}

void Ball::onInput(Ess3D::InputManager *inputManager) {
  float velocity = 30.f;
  glm::vec2 direction = glm::vec2(0.0f);

  if (inputManager->hasMouseMoved()) {
    glm::vec2 cursorDeltaPosition = inputManager->getCursorDeltaPosition();

    if (glm::length(cursorDeltaPosition) > 0) {
      cursorDeltaPosition = glm::normalize(cursorDeltaPosition);

      direction += cursorDeltaPosition;
      direction.y = -direction.y;
    }
  }

  this->setVelocity(direction * velocity);
}

void Ball::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}
