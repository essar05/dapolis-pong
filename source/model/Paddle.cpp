#include "Paddle.h"

Paddle::Paddle() = default;
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Paddle::~Paddle() = default;

bool Paddle::update(float deltaTime) {
  _position += _velocity * deltaTime;

  return true;
}

void Paddle::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}