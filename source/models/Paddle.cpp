#include "Paddle.h"
#include <Ess3D/input/InputManager.h>
#include <Ess3D/2d/utils/Utils2D.h>

Paddle::Paddle() = default;
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv) :
  Entity(position, size, textureId, uv) {}

Paddle::~Paddle() = default;

bool Paddle::onUpdate(float deltaTime) {
    _body->SetLinearVelocity(Ess3D::Utils2D::toB2Vec2(_velocity));
    _body->SetAngularVelocity(glm::radians(_angleDegree));

  return true;
}

void Paddle::initializeBody(b2World* world) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(_position.x, _position.y);
    bodyDef.angle = glm::radians(0.0f);

    _body = world->CreateBody(&bodyDef);
}

void Paddle::initializeFixtures(b2World* world) {
    b2PolygonShape shape;
    shape.SetAsBox(_size.x / 2, _size.y / 2);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.f; //0, as otherwise the ball will slowly lose velocity over time
    fixtureDef.restitution = 1.f; // "bounciness"
    _body->CreateFixture(&fixtureDef);
}

void Paddle::onInput(Ess3D::InputManager *inputManager) {
  glm::vec2 direction = glm::vec2(0.f);
  float velocity = 20.f;
  float angle = 0;
    
  if (inputManager->isKeyDown(_moveUpKeyId)) {
    direction += glm::vec2(0.0f, 1.0f);
  }
  if (inputManager->isKeyDown(_moveDownKeyId)) {
    direction += glm::vec2(0.0f, -1.0f);
  }
  if (inputManager->isKeyDown(_moveLeftKeyId)) {
      angle = 360; //this is used with SetAngularVelocity which changes over 1 second
  }
  if (inputManager->isKeyDown(_moveRightKeyId)) {
      angle = -360; //this is used with SetAngularVelocity which changes over 1 second
  }

  this->setVelocity(direction * velocity);
  this->setAngleDegree(angle);
}

void Paddle::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}

void Paddle::setAngleDegree(float angleDegree) {
    _angleDegree = angleDegree;
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

unsigned int Paddle::getMoveLeftKeyId() const {
    return _moveLeftKeyId;
}

void Paddle::setMoveLeftKeyId(unsigned int moveLeftKeyId) {
    _moveLeftKeyId = moveLeftKeyId;
}

unsigned int Paddle::getMoveRightKeyId() const {
    return _moveRightKeyId;
}

void Paddle::setMoveRightKeyId(unsigned int moveRightKeyId) {
    _moveRightKeyId = moveRightKeyId;
}
