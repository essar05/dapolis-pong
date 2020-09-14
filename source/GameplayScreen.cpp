#include "GameplayScreen.h"
#include <SDL_events.h>
#include <Ess3D/resources/TextureAtlas.h>

GameplayScreen::GameplayScreen() {
  _game = Game::GetInstance();
  _textureCache = Ess3D::TextureCache::getInstance();
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
  _fboRenderer = new Ess3D::FBORenderer();
  _fboRenderer->initShader();
  _sceneFBO = new Ess3D::FrameBufferObject(_game->getWindow(), (GLsizei) _game->getWidth(), (GLsizei) _game->getHeight(), Ess3D::DepthBufferType::TEXTURE);
  _sceneRenderer = new SceneRenderer(_game->getWidth(), _game->getHeight());

  Ess3D::TextureAtlas* atlas = _textureCache->getAtlas("Textures/atlas.png", "Textures/atlas.json");

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

void GameplayScreen::destroy() {
  delete _fboRenderer;
  delete _sceneFBO;
  delete _sceneRenderer;
}

void GameplayScreen::draw() {
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //bind FBO, all rendering will be done to this FBO's color buffer
  _sceneFBO->bind();
  
  //render scene
  _sceneRenderer->render();

  //unbind FBO, rendering will now be done to screen
  _sceneFBO->unbind();

  _fboRenderer->render(_sceneFBO);
}

void GameplayScreen::update(float deltaTime, int simulationSteps) {
  for(int i = 0; i < simulationSteps; i++) {
    processInput(deltaTime);

    _ball->resetInterpolation();
    _paddleLeft->resetInterpolation();
    _paddleRight->resetInterpolation();
    _sceneRenderer->getCamera()->resetSmoothState();

    _ball->update(deltaTime);
    _paddleLeft->update(deltaTime);
    _paddleRight->update(deltaTime);
  }

  _sceneRenderer->getCamera()->smoothState(_game->getTimestepAccumulator()->getAccumulatorRatio(), false);
  _ball->interpolate(_game->getTimestepAccumulator()->getAccumulatorRatio());
  _paddleLeft->interpolate(_game->getTimestepAccumulator()->getAccumulatorRatio());
  _paddleRight->interpolate(_game->getTimestepAccumulator()->getAccumulatorRatio());

  _sceneRenderer->getCamera()->update();
}

void GameplayScreen::processInput(float deltaTime) {
  SDL_Event event;
  Ess3D::InputManager* inputManager = _game->getInputManager();

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

  _sceneRenderer->getCamera()->setPosition(_sceneRenderer->getCamera()->getPosition() + cameraDirection * cameraVelocity);
  _ball->setVelocity(ballDirection * ballVelocity);
  _paddleLeft->setVelocity(paddleLeftDirection * paddleLeftVelocity);
  _paddleRight->setVelocity(paddleRightDirection * paddleRightVelocity);
}

SceneRenderer *GameplayScreen::getSceneRendered() {
  return this->_sceneRenderer;
}

Ball *GameplayScreen::getBall() {
  return this->_ball;
}

Paddle* GameplayScreen::getPaddleLeft() {
    return this->_paddleLeft;
}

Paddle* GameplayScreen::getPaddleRight() {
    return this->_paddleRight;
}
