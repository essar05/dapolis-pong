#ifndef DAPOLIS_PONG_SCENE_H
#define DAPOLIS_PONG_SCENE_H

#include <Ess3D/2d/Scene2D.h>
#include "../models/Ball.h"
#include "../models/Paddle.h"

class Scene : public Ess3D::Scene2D {
  public:
    Scene();

    virtual ~Scene();

    Ball* getBall();
    Paddle* getPaddleLeft();
    Paddle* getPaddleRight();

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;
    void onRender(Ess3D::Renderer2D *renderer) override;

    Ball* _ball{};
    Paddle* _paddleLeft{};
    Paddle* _paddleRight{};

};

#endif
