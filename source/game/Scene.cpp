#include <Ess3D/core/Config.h>
#include <Ess3D/core/State.h>
#include <Ess3D/2d/rendering/Renderer2D.h>
#include "Scene.h"

Scene::Scene() {
  _world = std::make_unique<World>();

  _quadTreeRenderer = std::make_unique<Ess3D::QuadTreeRenderer>();

  // set the camera to view the entire world's width
  _camera->setWidth(_world->getWidth());

  // set the border edges of the world to the camera's edges
  _world->buildWorldBorders(_camera->getSize());
}

Scene::~Scene() = default;

bool Scene::onUpdate(float deltaTime) {
  _camera->resetInterpolation();
  _camera->update();

  _world->update(deltaTime);

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

  _world->input(inputManager);
}

void Scene::onRender(Ess3D::Renderer2D *renderer) {
  _camera->interpolate(Ess3D::State::get()->getTimestepAccumulator()->getAccumulatorRatio(), false);

  _world->render(renderer);

  renderer->disableTexture();
  _world->getB2World()->DebugDraw();
  _quadTreeRenderer->renderTree(*renderer, *_world->getQuadTree());
}