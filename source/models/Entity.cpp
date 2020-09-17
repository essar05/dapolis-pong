#include "Entity.h"
#include "../Game.h"

Entity::Entity() = default;

Entity::Entity(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Object2D(position, size, textureId, uv) {}

void Entity::interpolate(float timestepAccumulatorRatio) {
  float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

  this->_interpolatedPosition = timestepAccumulatorRatio * _position +
    oneMinusRatio * _previousPosition;
}

void Entity::resetInterpolation() {
  _previousPosition = _position;
}

void Entity::initializePhysicsBody(b2World *world) {
  this->initializeBody(world);
  this->initializeFixtures(world);
}
