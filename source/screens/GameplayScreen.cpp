#include "GameplayScreen.h"
#include <SDL2/SDL_events.h>

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
  _renderer = new Ess3D::Renderer2D();

  this->initGUI();
}

void GameplayScreen::destroy() {
  delete _scene;
  delete _renderer;

  _gui.destroy();
}

void GameplayScreen::step(float deltaTime) {
  _scene->update(deltaTime);
}

void GameplayScreen::update() {
  this->updateGUI();
}

void GameplayScreen::input(Ess3D::InputManager *inputManager) {
  if(inputManager->isKeyDown(SDLK_ESCAPE)) {
    _currentState = Ess3D::ScreenState::EXIT_APPLICATION;
  }

  _scene->input(inputManager);
}

void GameplayScreen::render() {
  _scene->render(_renderer);

  _gui.draw();
}

void GameplayScreen::onSDLEvent(SDL_Event &event) {
  _gui.onSDLEvent(event);

  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F3) {
    Ess3D::Config* config = Ess3D::Config::get();
    if (config->isInterpolationEnabled()) {
      printf("Disabling interpolation \n");
      Ess3D::Config::get()->disableInterpolation();
    } else {
      printf("Enabling interpolation \n");
      Ess3D::Config::get()->enableInterpolation();
    }
  }
}

void GameplayScreen::initGUI() {
  _gui.init("gui");
  _gui.loadScheme("Pong.scheme");
  _gui.setFont("Soredona-18");

  _gui.loadLayout("hud.layout");
}

void GameplayScreen::updateGUI() {
  // TODO: Performance/efficiency ? Is it worth implementing a state
  //  and updating only on change ?
  _gui.getRootWindow()->getChild("HUD/ScoreValue")->setText("0 - 0");
}