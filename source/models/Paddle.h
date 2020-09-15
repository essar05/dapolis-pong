#ifndef DAPOLIS_PONG_PADDLE_H
#define DAPOLIS_PONG_PADDLE_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <SDL_keycode.h>
#include "Entity.h"

class Paddle : public Entity {
public:
    Paddle();
    Paddle(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv);
    ~Paddle();

    void setVelocity(const glm::vec2& velocity);

    unsigned int getMoveUpKeyId() const;
    void setMoveUpKeyId(unsigned int moveUpKeyId);

    unsigned int getMoveDownKeyId() const;
    void setMoveDownKeyId(unsigned int moveDownKeyId);

  protected:
    bool onUpdate(float deltaTime) override;
    void onInput(Ess3D::InputManager *inputManager) override;

    glm::vec2 _velocity;

    unsigned int _moveUpKeyId = SDLK_w;
    unsigned int _moveDownKeyId = SDLK_s;

};

#endif //DAPOLIS_PONG_BALL_H
