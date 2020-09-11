#include "Ball.h"
#include "Game.h"

Ball::Ball() = default;

Ball::Ball(int textureId, glm::vec4 uv, float width, float height, glm::vec2 position) {
  _color = Ess3D::ColorRGBA8(225, 255, 255, 255);
  _width = Game::GetInstance()->getGameplayScreen()->getSceneRendered()->getCamera()->getWorldScalar(width);
  _height = Game::GetInstance()->getGameplayScreen()->getSceneRendered()->getCamera()->getWorldScalar(height);
  _position = Game::GetInstance()->getGameplayScreen()->getSceneRendered()->getCamera()->getWorldCoordinates(position);
  _textureId = textureId;
  _uv = uv;
}

Ball::~Ball() = default;

void Ball::draw() {
  Ess3D::SpriteBatch* spriteBatch = Game::GetInstance()->getGameplayScreen()->getSceneRendered()->getSpriteBatch();
  spriteBatch->draw(glm::vec4(_drawPosition.x - _width / 2, _drawPosition.y - _height / 2, _width, _height), _uv, _textureId, _color, 9000.0f, 0.0f);
}

bool Ball::update(float deltaTime) {
  _position += _velocity * deltaTime;

  return true;
}

void Ball::setVelocity(const glm::vec2& velocity) {
	_velocity = velocity;
}

void Ball::smoothStates(float timestepAccumulatorRatio) {
  float oneMinusRatio = 1.0f - timestepAccumulatorRatio;

  this->_drawPosition = timestepAccumulatorRatio * _position +
      oneMinusRatio * _previousPosition;
}

void Ball::resetSmoothStates() {
  _previousPosition = _position;
}
