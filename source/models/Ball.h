#ifndef DAPOLIS_PONG_BALL_H
#define DAPOLIS_PONG_BALL_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include "Entity.h"

class Ball : public Entity {
  public:
    Ball();
    Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv);
    ~Ball();

    void setDirection(const glm::vec2& direction);

    void interpolate(float timestepAccumulatorRatio) override;
    void resetInterpolation() override;

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;

    void initializeBody(b2World *world) override;
    void initializeFixtures(b2World *world) override;

    glm::vec2 _direction;
    float _velocity = 5.5f;

};

#endif //DAPOLIS_PONG_BALL_H
