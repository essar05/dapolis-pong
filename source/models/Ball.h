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

    void setVelocity(const glm::vec2& velocity);

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;

    glm::vec2 _velocity;

};

#endif //DAPOLIS_PONG_BALL_H
