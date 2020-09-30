#ifndef DAPOLIS_PONG_SCENE_H
#define DAPOLIS_PONG_SCENE_H

#include <memory>
#include <Ess3D/2d/Scene2D.h>
#include <Ess3D/data/QuadTree.h>
#include <Ess3D/2d/rendering/QuadTreeRenderer.h>
#include "../models/Ball.h"
#include "../models/Paddle.h"
#include "World.h"

class Scene : public Ess3D::Scene2D {
  public:
    Scene();

    virtual ~Scene();

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;
    void onRender(Ess3D::Renderer2D *renderer) override;

    std::unique_ptr<World> _world;
    std::unique_ptr<Ess3D::QuadTreeRenderer> _quadTreeRenderer = nullptr;

};

#endif
