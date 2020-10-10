#ifndef DAPOLIS_PONG_BALL_H
#define DAPOLIS_PONG_BALL_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include "Entity.h"
#include <string>

class Ball : public Entity {
  public:
    Ball();
    Ball(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv, std::string id);
    ~Ball();

    void applyImpulse(const glm::vec2& direction);

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;

    void initializeBody(b2World *world) override;
    void initializeFixtures(b2World *world) override;

    glm::vec2 _impulse = glm::vec2(0.f);
    float _impulseMagnitude = 15.0f;

};

#endif //DAPOLIS_PONG_BALL_H
