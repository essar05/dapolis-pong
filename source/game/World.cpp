#include <random>
#include <Ess3D/resources/TextureCache.h>
#include "World.h"

World::World() {
  _b2World = std::make_shared<b2World>(b2Vec2(0, 0));
  _b2World->SetAutoClearForces(false);
  _b2World->SetDebugDraw(&_b2DebugRenderer);
  _b2DebugRenderer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);

  Ess3D::TextureAtlas* atlas = Ess3D::TextureCache::getInstance()->getAtlas("textures/atlas.png", "textures/atlas.json");

  _ball = std::make_shared<Ball>(
    glm::vec2(0.f, 0.f),
    glm::vec2(1.f, 1.f),
    atlas->getTexture()->getId(),
    atlas->getUV("cluster_bomb")
  );
  _ball->initializePhysicsBody(_b2World.get());

  std::random_device randomDevice;
  std::mt19937 randomGenerator(randomDevice());
  std::uniform_real_distribution<double> distribution(1.0, 10.0);
  glm::vec2 ballDirection = glm::normalize(glm::vec2(distribution(randomGenerator), distribution(randomGenerator)));
  _ball->setDirection(ballDirection);

  _paddleLeft = std::make_shared<Paddle>(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(-22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("paddle_red")
  );
  _paddleLeft->initializePhysicsBody(_b2World.get());

  _paddleRight = std::make_shared<Paddle>(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("paddle_black")
  );
  _paddleLeft->initializePhysicsBody(_b2World.get());
  _paddleRight->setMoveUpKeyId(SDLK_o);
  _paddleRight->setMoveDownKeyId(SDLK_l);
}

void World::render(Ess3D::Renderer2D *renderer) {
  _ball->render(renderer);
  _paddleLeft->render(renderer);
  _paddleRight->render(renderer);
}

void World::input(Ess3D::InputManager *inputManager) {
  _ball->input(inputManager);
  _paddleLeft->input(inputManager);
  _paddleRight->input(inputManager);
}

bool World::update(float deltaTime) {
  _ball->update(deltaTime);
  _paddleLeft->update(deltaTime);
  _paddleRight->update(deltaTime);

  //iterate b2 world
  _b2World->Step(deltaTime, 8, 3);

  return true;
}

Ball *World::getBall() {
  return _ball.get();
}

Paddle *World::getPaddleLeft() {
  return _paddleLeft.get();
}

Paddle *World::getPaddleRight() {
  return _paddleRight.get();
}

b2World *World::getB2World() {
  return _b2World.get();
}
