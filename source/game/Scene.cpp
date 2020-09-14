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
}

Scene::~Scene() = default;

void Scene::render(Ess3D::Renderer2D *renderer) {
  _ball->draw(renderer);
}

void Scene::update(float deltaTime) {
  _ball->update(deltaTime);
  _camera->update();
}

void Scene::interpolate(float timestepAccumulatorRatio) {
  _camera->smoothState(timestepAccumulatorRatio, false);
  _ball->interpolate(timestepAccumulatorRatio);
}

void Scene::resetInterpolation() {
  _ball->resetInterpolation();
  _camera->resetSmoothState();
}

Ball *Scene::getBall() {
  return _ball;
}

