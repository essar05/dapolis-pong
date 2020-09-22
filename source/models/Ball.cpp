#include "Ball.h"
#include <Ess3D/input/InputManager.h>
#include <Ess3D/2d/utils/Utils2D.h>

Ball::Ball() = default;
Ball::Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Ball::~Ball() = default;

bool Ball::onUpdate(float deltaTime) {
  // if the magnitude of the impulse vector is > 0
  if (glm::length(_impulse) > 0.f) {
    // apply impulse
    _body->ApplyLinearImpulseToCenter(Ess3D::Utils2D::toB2Vec2(_impulse), true);
    _body->ApplyTorque(15.0f, true); // spin the ball just for fun

    // reset the impulse
    _impulse = glm::vec2(0.f);
  }

  return true;
}

void Ball::applyImpulse(const glm::vec2 &direction) {
  _impulse = direction * _impulseMagnitude;
}

void Ball::onInput(Ess3D::InputManager *inputManager) {}

void Ball::initializeBody(b2World *world) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(_position.x, _position.y);
  bodyDef.angle = glm::radians(0.0f);

  _body = world->CreateBody(&bodyDef);
}

void Ball::initializeFixtures(b2World *world) {
  b2CircleShape shape;
  shape.m_radius = _size.x / 2;

  b2FixtureDef definition;
  definition.shape = &shape;
  definition.density = 1.0f;
  definition.friction = 0.f; //0, as otherwise the ball will slowly lose velocity over time
  definition.restitution = 1.f; // "bounciness"
  _body->CreateFixture(&definition);
}