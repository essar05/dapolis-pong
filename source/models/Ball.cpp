#include "Ball.h"
#include <Ess3D/input/InputManager.h>
#include <Ess3D/2d/utils/Utils2D.h>

Ball::Ball() = default;
Ball::Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Ball::~Ball() = default;

bool Ball::onUpdate(float deltaTime) {
  _body->SetLinearVelocity(Ess3D::Utils2D::toB2Vec2(_direction * _velocity));

  return true;
}

void Ball::onInput(Ess3D::InputManager *inputManager) {

}

void Ball::initializeBody(b2World *world) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(_position.x, _position.y);
  bodyDef.angle = glm::radians(0.0f);
  bodyDef.fixedRotation = true;

  _body = world->CreateBody(&bodyDef);
}

void Ball::initializeFixtures(b2World *world) {
  b2CircleShape shape;
  shape.m_radius = _size.x / 2;

  b2FixtureDef definition;
  definition.shape = &shape;
  definition.density = 1.0f;
  _body->CreateFixture(&definition);
}

void Ball::setDirection(const glm::vec2& direction) {
	_direction = direction;
}

void Ball::interpolate(float timestepAccumulatorRatio) {
  float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

  this->_interpolatedPosition = timestepAccumulatorRatio * Ess3D::Utils2D::toVec2(_body->GetPosition()) +
                                oneMinusRatio * _previousPosition;
}

void Ball::resetInterpolation() {
  glm::vec2 position = Ess3D::Utils2D::toVec2(_body->GetPosition());
  _previousPosition = position;
}
