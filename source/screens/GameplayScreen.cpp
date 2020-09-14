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

void GameplayScreen::draw() {
  _sceneRenderer->render(_scene);
}

void GameplayScreen::update(float deltaTime, int simulationSteps) {
  for(int i = 0; i < simulationSteps; i++) {
    processInput(deltaTime);

    _scene->resetInterpolation();

    _scene->update(deltaTime);
  }

  _scene->interpolate(_state->getTimestepAccumulator()->getAccumulatorRatio());
}

void GameplayScreen::processInput(float deltaTime) {
  //TODO: Improve input handling (per scene / per object)

  SDL_Event event;
  Ess3D::InputManager* inputManager = _state->getInputManager();

  inputManager->reset();
  while(SDL_PollEvent(&event) != 0) {
    _game->onSDLEvent(event);
  }
 
  if(inputManager->isKeyDown(SDLK_ESCAPE)) {
    _currentState = Ess3D::ScreenState::EXIT_APPLICATION;
  }

  glm::vec2 ballDirection = glm::vec2(0.0f);
  glm::vec2 cameraDirection = glm::vec2(0.f);
  glm::vec2 paddleLeftDirection = glm::vec2(0.f);
  glm::vec2 paddleRightDirection = glm::vec2(0.f);

  float ballVelocity = 30.f;
  float cameraVelocity = 0.1f;
  float paddleLeftVelocity = 20.f;
  float paddleRightVelocity = 20.f;

  if (inputManager->hasMouseMoved()) {
    glm::vec2 cursorDeltaPosition = inputManager->getCursorDeltaPosition();

    if (glm::length(cursorDeltaPosition) > 0) {
      cursorDeltaPosition = glm::normalize(cursorDeltaPosition);

      ballDirection += cursorDeltaPosition;
      ballDirection.y = -ballDirection.y;
    }
  }

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

  //Controls for paddleLeft
  if (inputManager->isKeyDown(SDLK_w)) {
      paddleLeftDirection += glm::vec2(0.0f, 1.0f);
  }
  if (inputManager->isKeyDown(SDLK_s)) {
      paddleLeftDirection += glm::vec2(0.0f, -1.0f);
  }

  //Controls for paddleRight
  if (inputManager->isKeyDown(SDLK_o)) {
      paddleRightDirection += glm::vec2(0.0f, 1.0f);
  }
  if (inputManager->isKeyDown(SDLK_l)) {
      paddleRightDirection += glm::vec2(0.0f, -1.0f);
  }

  _scene->getCamera()->setPosition(_scene->getCamera()->getPosition() + cameraDirection * cameraVelocity);
  _scene->getBall()->setVelocity(ballDirection * ballVelocity);

//  _paddleLeft->setVelocity(paddleLeftDirection * paddleLeftVelocity);
//  _paddleRight->setVelocity(paddleRightDirection * paddleRightVelocity);
}

SceneRenderer *GameplayScreen::getSceneRenderer() {
  return this->_sceneRenderer;
}
