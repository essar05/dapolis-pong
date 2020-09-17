#include "Paddle.h"
#include <Ess3D/input/InputManager.h>

Paddle::Paddle() = default;
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Paddle::~Paddle() = default;

bool Paddle::onUpdate(float deltaTime) {
  _position += _velocity * deltaTime;

  return true;
}

void Paddle::onInput(Ess3D::InputManager *inputManager) {
  glm::vec2 direction = glm::vec2(0.f);
  float velocity = 20.f;

  if (inputManager->isKeyDown(_moveUpKeyId)) {
    direction += glm::vec2(0.0f, 1.0f);
  }
  if (inputManager->isKeyDown(_moveDownKeyId)) {
    direction += glm::vec2(0.0f, -1.0f);
  }

  this->setVelocity(direction * velocity);
}

void Paddle::initializeBody(b2World *world) {}

void Paddle::initializeFixtures(b2World *world) {}

void Paddle::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}

unsigned int Paddle::getMoveUpKeyId() const {
  return _moveUpKeyId;
}

void Paddle::setMoveUpKeyId(unsigned int moveUpKeyId) {
  _moveUpKeyId = moveUpKeyId;
}

unsigned int Paddle::getMoveDownKeyId() const {
  return _moveDownKeyId;
}

void Paddle::setMoveDownKeyId(unsigned int moveDownKeyId) {
  _moveDownKeyId = moveDownKeyId;
}

