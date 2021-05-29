#ifndef DAPOLIS_PONG_WORLD_H
#define DAPOLIS_PONG_WORLD_H

#include <Ess3D/2d/traits/IRenderable2D.h>
#include <Ess3D/core/traits/IHandlesInput.h>
#include <Ess3D/core/traits/IUpdatable.h>
#include <box2d/box2d.h>
#include <memory>
#include "../models/Ball.h"
#include "../models/Paddle.h"
#include <Ess3D/2d/rendering/B2DebugRenderer.h>
#include <Ess3D/data/QuadTree.h>

enum WorldBorderOrientation {
  HORIZONTAL,
  VERTICAL
};

// move to Ess3D
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
    Ess3D::QuadTree* getQuadTree();

    float getWidth();

    void buildWorldBorders(const glm::vec2& worldSize);

  protected:
    void initializeB2World();
    void buildWorldBorder(const glm::vec2& position, float length, WorldBorderOrientation orientation);

    std::unique_ptr<b2World> _b2World;
    Ess3D::B2DebugRenderer _b2DebugRenderer;
    std::unique_ptr<Ess3D::QuadTree> _quadTree;

    std::unique_ptr<Ball> _ball{};
    std::unique_ptr<Paddle> _paddleLeft{};
    std::unique_ptr<Paddle> _paddleRight{};

    float _width = 50.f;

};

#endif
