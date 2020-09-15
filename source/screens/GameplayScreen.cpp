#include "GameplayScreen.h"
#include <SDL_events.h>

GameplayScreen::GameplayScreen() {
  _game = Game::GetInstance();
  _config = Ess3D::Config::get();
  _state = Ess3D::State::get();

  _screenIndex = SCREEN_INDEX_GAMEPLAY;
}

GameplayScreen::~GameplayScreen() = default;

int GameplayScreen::getNextScreenIndex() const {
  return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
  return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::onEntry() {
  //Set to true to keep mouse in center always - this will work with getCursorDeltaPosition
  SDL_SetRelativeMouseMode(SDL_TRUE);
  //Set to true to show mouse cursor over screen
  //SDL_ShowCursor(SDL_TRUE);
}

void GameplayScreen::onExit() {}

void GameplayScreen::build() {
  _scene = new Scene();
  _sceneRenderer = new SceneRenderer();
}

void GameplayScreen::destroy() {
  delete _scene;
  delete _sceneRenderer;
}

void GameplayScreen::step(float deltaTime) {
  _scene->update(deltaTime);
}

void GameplayScreen::update() {}

void GameplayScreen::input(Ess3D::InputManager *inputManager) {
  if(inputManager->isKeyDown(SDLK_ESCAPE)) {
    _currentState = Ess3D::ScreenState::EXIT_APPLICATION;
  }

  _scene->input(inputManager);
}

void GameplayScreen::render() {
  _scene->render(_sceneRenderer);
}

SceneRenderer *GameplayScreen::getSceneRenderer() {
  return this->_sceneRenderer;
}