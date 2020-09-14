#include "Entity.h"
#include "../Game.h"

Entity::Entity() = default;

Entity::Entity(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Object2D(position, size, textureId, uv) {}

void Entity::draw(Ess3D::Renderer2D* renderer2D) {
  renderer2D->draw(
    glm::vec4(_interpolatedPosition.x - _size.x / 2, _interpolatedPosition.y - _size.y / 2, _size.x, _size.y),
    _uv, _textureId, _color, 9000.0f, 0.0f
  );
}

bool Entity::update(float deltaTime) {
  return true;
}

void Entity::interpolate(float timestepAccumulatorRatio) {
  float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

  this->_interpolatedPosition = timestepAccumulatorRatio * _position +
    oneMinusRatio * _previousPosition;
}

void Entity::resetInterpolation() {
  _previousPosition = _position;
}
