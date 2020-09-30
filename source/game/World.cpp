#include <random>
#include <Ess3D/resources/TextureCache.h>
#include "World.h"

World::World() {
  this->initializeB2World();

  Ess3D::TextureAtlas* atlas = Ess3D::TextureCache::getInstance()->getAtlas("textures/atlas.png","textures/atlas.json");

  _ball = std::make_unique<Ball>(
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
  _ball->applyImpulse(ballDirection);

  _paddleLeft = std::make_unique<Paddle>(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(-22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("new_paddle_orange")
  );
  _paddleLeft->initializePhysicsBody(_b2World.get());

  _paddleRight = std::make_unique<Paddle>(
    //TODO FIX : HARDCODED - must be screen width dependent
    glm::vec2(22.f, 0.f),
    glm::vec2(1.f, 8.f),
    atlas->getTexture()->getId(),
    atlas->getUV("new_paddle_blue")
  );
  _paddleRight->initializePhysicsBody(_b2World.get());
  _paddleRight->setMoveUpKeyId(SDLK_i);
  _paddleRight->setMoveDownKeyId(SDLK_k);
  _paddleRight->setMoveLeftKeyId(SDLK_j);
  _paddleRight->setMoveRightKeyId(SDLK_l);
}

void World::render( Ess3D::Renderer2D* renderer ) {
  _quadTree = std::make_unique<Ess3D::QuadTree>(glm::vec2(100.f, 100.f), 7, 1);

  Ess3D::BoundingBox ballBoundingBox = _ball->getBoundingBox();
  _quadTree->insert(0, ballBoundingBox);
  _quadTree->insert(1, _paddleLeft->getBoundingBox());
  _quadTree->insert(2, _paddleRight->getBoundingBox());
  _quadTree->insert(3, ballBoundingBox);
  _quadTree->insert(4, ballBoundingBox);
  _quadTree->insert(5, ballBoundingBox);
  _quadTree->insert(6, ballBoundingBox);

  _ball->render(renderer);
  _paddleLeft->render(renderer);
  _paddleRight->render(renderer);
}

void World::input( Ess3D::InputManager* inputManager ) {
  _ball->input(inputManager);
  _paddleLeft->input(inputManager);
  _paddleRight->input(inputManager);
}

bool World::update( float deltaTime ) {
  _ball->update(deltaTime);
  _paddleLeft->update(deltaTime);
  _paddleRight->update(deltaTime);

  //iterate b2 world
  _b2World->Step(deltaTime, 8, 3);

  return true;
}

Ball* World::getBall() {
  return _ball.get();
}

Paddle* World::getPaddleLeft() {
  return _paddleLeft.get();
}

Paddle* World::getPaddleRight() {
  return _paddleRight.get();
}

b2World* World::getB2World() {
  return _b2World.get();
}

void World::initializeB2World() {
  _b2World = std::make_unique<b2World>(b2Vec2(0, 0));
  _b2World->SetAutoClearForces(true);
  _b2World->SetDebugDraw(&_b2DebugRenderer);
  _b2DebugRenderer.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
}

void World::buildWorldBorders( const glm::vec2& worldSize ) {
  //TOP
  this->buildWorldBorder(glm::vec2(0.f, worldSize.y / 2), worldSize.x, WorldBorderOrientation::HORIZONTAL);
  //BOTTOM
  this->buildWorldBorder(glm::vec2(0.f, -worldSize.y / 2), worldSize.x, WorldBorderOrientation::HORIZONTAL);
  //LEFT
  this->buildWorldBorder(glm::vec2(-worldSize.x / 2, 0.f), worldSize.y, WorldBorderOrientation::VERTICAL);
  //RIGHT
  this->buildWorldBorder(glm::vec2(worldSize.x / 2, 0.f), worldSize.y, WorldBorderOrientation::VERTICAL);
}

void World::buildWorldBorder( const glm::vec2& position, float length, WorldBorderOrientation orientation ) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_staticBody;
  bodyDef.position.Set(position.x, position.y);
  bodyDef.angle = glm::radians(0.0f);

  b2Body* edge = _b2World->CreateBody(&bodyDef);

  b2Vec2 pointA = b2Vec2(
    orientation == WorldBorderOrientation::HORIZONTAL ? -length / 2 : 0.f,
    orientation == WorldBorderOrientation::VERTICAL ? -length / 2 : 0.f
  );
  b2Vec2 pointB = b2Vec2(
    orientation == WorldBorderOrientation::HORIZONTAL ? length / 2 : 0.f,
    orientation == WorldBorderOrientation::VERTICAL ? length / 2 : 0.f
  );

  b2EdgeShape shape;
  shape.SetTwoSided(pointA, pointB);

  b2FixtureDef definition;
  definition.shape = &shape;
  //definition.friction = 100.f;
  edge->CreateFixture(&definition);
}

float World::getWidth() {
  return _width;
}

Ess3D::QuadTree* World::getQuadTree() {
  return _quadTree.get();
}
