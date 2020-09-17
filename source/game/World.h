#ifndef DAPOLIS_PONG_WORLD_H
#define DAPOLIS_PONG_WORLD_H

#include <Ess3D/2d/traits/IRenderable2D.h>
#include <Ess3D/core/traits/IHandlesInput.h>
#include <Ess3D/core/traits/IUpdatable.h>
#include <Box2D/box2d.h>
#include <memory>
#include "../models/Ball.h"
#include "../models/Paddle.h"
#include "../rendering/B2DebugRenderer.h"

class World : public Ess3D::IUpdatable, public Ess3D::IHandlesInput, public Ess3D::IRenderable2D {
  public:
    World();

    bool update(float deltaTime) override;
    void input(Ess3D::InputManager *inputManager) override;
    void render(Ess3D::Renderer2D *renderer) override;

    b2World* getB2World();

    Ball* getBall();
    Paddle* getPaddleLeft();
    Paddle* getPaddleRight();

  protected:
    std::shared_ptr<b2World> _b2World;
    B2DebugRenderer _b2DebugRenderer;

    std::shared_ptr<Ball> _ball{};
    std::shared_ptr<Paddle> _paddleLeft{};
    std::shared_ptr<Paddle> _paddleRight{};

};

#endif
