#include "Paddle.h"
#include "./../game/World.h"
#include <Ess3D/input/InputManager.h>
#include <Ess3D/2d/utils/Utils2D.h>

Paddle::Paddle() = default;
Paddle::Paddle(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv, std::string name, const World &world) :
  Entity(position, size, textureId, uv, name), _world(&world) {}

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
  if (inputManager->isKeyDown(SDLK_F1) && this->hasId("paddle left")) {
    this->setAiEnabled(true);
  }
  if (inputManager->isKeyDown(SDLK_F2) && this->hasId("paddle right")) {
    this->setAiEnabled(true);
  }
  if (inputManager->isKeyDown(SDLK_F8)) {
    this->setAiEnabled(false);
  }


  //Handle AI controls - maybe not the best place - extract later into World?
  if (this->getAiEnabled()) {

    bool isBallGoingLeft = _world->getBall()->getBody()->GetLinearVelocity().x < 0;
    bool isBallAbovePaddle = _world->getBall()->getBody()->GetPosition().y > (this->getBody()->GetPosition().y + (_size.y / 2));
    bool isBallBelowPaddle = _world->getBall()->getBody()->GetPosition().y < (this->getBody()->GetPosition().y - (_size.y / 2));
    bool isBallApproaching = (this->hasId("paddle left") && isBallGoingLeft) || (this->hasId("paddle right") && !isBallGoingLeft);

    //move paddle only if ball outside of paddle range(it's length)
    if (isBallApproaching && (isBallAbovePaddle || isBallBelowPaddle)) {
      direction = glm::vec2(0.f, isBallAbovePaddle ? 1.0f : -1.0f);
    }
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

bool Paddle::getAiEnabled() {
  return _aiEnabled;
}

void Paddle::setAiEnabled(bool aiEnabled) {
  _aiEnabled = aiEnabled;
}
