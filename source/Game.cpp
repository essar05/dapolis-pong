#define NOMINMAX

#include "Game.h"

Game::Game() = default;

Game::~Game() = default;

Game* Game::instance = nullptr;

void Game::addScreens() {
  _gameplayScreen = new GameplayScreen();

  _screenManager->addScreen(_gameplayScreen);
  _screenManager->setScreen(_gameplayScreen->getIndex());
}

void Game::onInit() {
  _config->setTitle("DAPOLIS // pong");
  _config->setWidth(1300.f);
  _config->setHeight(700.f);
  _config->setVSync(true);
}

void Game::onExit() {
  delete _gameplayScreen;
}

void Game::onUpdate() {}

Game* Game::GetInstance() {
  if (instance == nullptr) {
    instance = new Game();
  }

  return instance;
}

GameplayScreen* Game::getGameplayScreen() {
  return _gameplayScreen;
}
