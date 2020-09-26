#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "screens/GameplayScreen.h"
#include <Ess3D/core/IGame.h>

class GameplayScreen;

class Game : public Ess3D::IGame {
  public:
    static Game* GetInstance();
    ~Game();

    virtual void addScreens() override;
    virtual void onInit() override;
    virtual void onExit() override;

    GameplayScreen* getGameplayScreen();

  protected:
    Game();

    virtual void onUpdate() override;

  private:
    static Game* instance;
    GameplayScreen* _gameplayScreen{};

};

#endif // GAME_H
