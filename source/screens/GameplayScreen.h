#pragma once

#include <Ess3D/core/IGameScreen.h>
#include <Ess3D/core/Config.h>
#include <Ess3D/core/State.h>
#include "../Game.h"
#include "ScreenIndices.h"
#include "../rendering/SceneRenderer.h"
#include "../game/Scene.h"
#include "../models/Ball.h"

class Game;

class GameplayScreen : public Ess3D::IGameScreen {
  public:
    GameplayScreen();
    ~GameplayScreen();

    int getNextScreenIndex() const override;
    int getPreviousScreenIndex() const override;

    SceneRenderer* getSceneRenderer();

    void build() override;
    void destroy() override;
    void draw() override;
    void update(float deltaTime, int simulationSteps) override;

    void onEntry() override;
    void onExit() override;
    
  private:
    void processInput(float deltaTime);

    Game* _game = nullptr;

    Ess3D::Config* _config;
    Ess3D::State* _state;

    SceneRenderer* _sceneRenderer{};
    Scene* _scene{};

};

