#pragma once

#include <Ess3D/core/IGameScreen.h>
#include <Ess3D/gl/FBORenderer.h>
#include <Ess3D/resources/TextureCache.h>
#include "Game.h"
#include "ScreenIndices.h"
#include "SceneRenderer.h"
#include "Ball.h"

class Game;

class GameplayScreen : public Ess3D::IGameScreen {
  public:
    GameplayScreen();
    ~GameplayScreen();

    int getNextScreenIndex() const override;
    int getPreviousScreenIndex() const override;

    SceneRenderer* getSceneRendered();
    Ball* getBall();

    void build() override;
    void destroy() override;
    void draw() override;
    void update(float deltaTime, int simulationSteps) override;

    void onEntry() override;
    void onExit() override;
    
  private:
    void processInput(float deltaTime);
    
    Game* _game = nullptr;
    SceneRenderer* _sceneRenderer;
    Ball* _ball;

    Ess3D::TextureCache* _textureCache;

    Ess3D::FrameBufferObject* _sceneFBO;
    Ess3D::FBORenderer* _fboRenderer;

};
