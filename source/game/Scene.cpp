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
}

Scene::~Scene() = default;

void Scene::render(Ess3D::Renderer2D *renderer) {
  _ball->draw(renderer);
  _paddleLeft->draw(renderer);
  _paddleRight->draw(renderer);
}

void Scene::update(float deltaTime) {
  _ball->update(deltaTime);
  _paddleLeft->update(deltaTime);
  _paddleRight->update(deltaTime);
  _camera->update();
}

void Scene::interpolate(float timestepAccumulatorRatio) {
  _camera->smoothState(timestepAccumulatorRatio, false);
  _ball->interpolate(timestepAccumulatorRatio);
  _paddleLeft->interpolate(timestepAccumulatorRatio);
  _paddleRight->interpolate(timestepAccumulatorRatio);
}

void Scene::resetInterpolation() {
  _ball->resetInterpolation();
  _paddleLeft->resetInterpolation();
  _paddleRight->resetInterpolation();
  _camera->resetSmoothState();
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

