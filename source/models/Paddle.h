#ifndef DAPOLIS_PONG_PADDLE_H
#define DAPOLIS_PONG_PADDLE_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <SDL_keycode.h>
#include <Ess3D/2d/models/Entity2D.h>

class Paddle : public Ess3D::Entity2D {
  public:
    Paddle();
    Paddle(const glm::vec2 &position, const glm::vec2 &size, GLuint textureId, const glm::vec4 &uv);

    ~Paddle();

    void setVelocity(const glm::vec2 &velocity);

    float getAngularVelocity() const;
    void setAngularVelocity(float angleDegree);

    unsigned int getMoveUpKeyId() const;
    void setMoveUpKeyId(unsigned int moveUpKeyId);

    unsigned int getMoveDownKeyId() const;
    void setMoveDownKeyId(unsigned int moveDownKeyId);

    unsigned int getMoveLeftKeyId() const;
    void setMoveLeftKeyId(unsigned int moveLeftKeyId);

    unsigned int getMoveRightKeyId() const;
    void setMoveRightKeyId(unsigned int moveRightKeyId);

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;

    void initializeBody(b2World *world) override;
    void initializeFixtures(b2World *world) override;

    glm::vec2 _velocity;
    float _angularVelocity;

    unsigned int _moveUpKeyId = SDLK_w;
    unsigned int _moveDownKeyId = SDLK_s;
    unsigned int _moveLeftKeyId = SDLK_a;
    unsigned int _moveRightKeyId = SDLK_d;

};

#endif //DAPOLIS_PONG_BALL_H
