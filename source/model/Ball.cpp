#include "Ball.h"

Ball::Ball() = default;
Ball::Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Ball::~Ball() = default;

bool Ball::update(float deltaTime) {
  _position += _velocity * deltaTime;

  return true;
}

void Ball::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}