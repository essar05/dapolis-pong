#include "Entity.h"
#include "../Game.h"
#include <Ess3D/2d/utils/Utils2D.h>

Entity::Entity() = default;

Entity::Entity(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv, std::string id) :
  Object2D(position, size, textureId, uv), _id(id) {}

void Entity::interpolate(float timestepAccumulatorRatio) {
    float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

    this->_interpolatedPosition = timestepAccumulatorRatio * Ess3D::Utils2D::toVec2(_body->GetPosition()) +
        oneMinusRatio * _previousPosition;

    // TODO: have a _previousAngle.
    // TODO: ? come up with some sort of Interpolatable class to avoid having 3 separate members for one particular object property
    this->_angle = timestepAccumulatorRatio * _body->GetAngle() + oneMinusRatio * _angle;
}

void Entity::resetInterpolation() {
    glm::vec2 position = Ess3D::Utils2D::toVec2(_body->GetPosition());
    _previousPosition = position;
}

void Entity::initializePhysicsBody(b2World *world) {
  this->initializeBody(world);
  this->initializeFixtures(world);
}


b2Body* Entity::getBody() {
  return _body;
}

std::string Entity::getId() {
  return _id;
}

bool Entity::hasId(std::string id) {
  return _id == id;
}
