#include <Ess3D/core/Config.h>
#include <Ess3D/resources/TextureCache.h>
#include <Ess3D/core/State.h>
#include "Scene.h"

Scene::Scene() {
  Ess3D::TextureAtlas* atlas = Ess3D::TextureCache::getInstance()->getAtlas("textures/atlas.png", "textures/atlas.json");

  _ball = new Ball(
    glm::vec2(0.f, 0.f),
    glm::vec2(1.f, 1.f),
    atlas->getTexture()->getId(),
    atlas->getUV("cluster_bomb")
  );

  _paddleLeft = new Paddle(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(-22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("paddle_red")
  );

  _paddleRight = new Paddle(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("paddle_black")
  );
  _paddleRight->setMoveUpKeyId(SDLK_o);
  _paddleRight->setMoveDownKeyId(SDLK_l);
}

Scene::~Scene() = default;

bool Scene::onUpdate(float deltaTime) {
  _camera->resetInterpolation();

  _camera->update();
  _ball->update(deltaTime);
  _paddleLeft->update(deltaTime);
  _paddleRight->update(deltaTime);

  return true;
}

void Scene::onInput(Ess3D::InputManager *inputManager) {
  glm::vec2 cameraDirection = glm::vec2(0.f);
  float cameraVelocity = 0.1f;

  if (inputManager->isKeyDown(SDLK_UP)) {
    cameraDirection += glm::vec2(0.0f, 1.0f);
  }
  if (inputManager->isKeyDown(SDLK_DOWN)) {
    cameraDirection += glm::vec2(0.0f, -1.0f);
  }
  if (inputManager->isKeyDown(SDLK_LEFT)) {
    cameraDirection += glm::vec2(-1.0f, 0.0f);
  }
  if (inputManager->isKeyDown(SDLK_RIGHT)) {
    cameraDirection += glm::vec2(1.0f, 0.0f);
  }

  _camera->setPosition(_camera->getPosition() + cameraDirection * cameraVelocity);

  _ball->input(inputManager);
  _paddleLeft->input(inputManager);
  _paddleRight->input(inputManager);
}

void Scene::onRender(Ess3D::Renderer2D *renderer) {
  _camera->interpolate(Ess3D::State::get()->getTimestepAccumulator()->getAccumulatorRatio(), false);

  _ball->render(renderer);
  _paddleLeft->render(renderer);
  _paddleRight->render(renderer);
}

Ball *Scene::getBall() {
  return _ball;
}

Paddle *Scene::getPaddleLeft() {
  return _paddleLeft;
}

Paddle *Scene::getPaddleRight() {
  return _paddleRight;
}
