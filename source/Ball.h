#ifndef DAPOLIS_PONG_BALL_H
#define DAPOLIS_PONG_BALL_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <Ess3D/gl/ColorRGBA8.h>

class Ball {
  public:
    Ball();
    Ball(int textureId, const glm::vec4& uv, float width, float height, const glm::vec2& position);
    ~Ball();

    void draw();
    bool update(float deltaTime);
    void setVelocity(const glm::vec2& velocity);

    void smoothStates(float timestepAccumulatorRatio);
    void resetSmoothStates();

  protected:
    float _width{};
    float _height{};

    glm::vec2 _previousPosition;
    glm::vec2 _position;
    // only used for rendering
    glm::vec2 _interpolatedPosition;

    glm::vec2 _velocity;

    // render information
    GLuint _textureId{};
    glm::vec4 _uv;
    Ess3D::ColorRGBA8 _color;
};

#endif //DAPOLIS_PONG_BALL_H
