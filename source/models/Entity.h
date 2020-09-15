#ifndef DAPOLIS_PONG_ENTITY_H
#define DAPOLIS_PONG_ENTITY_H

#include <Ess3D/2d/models/Object2D.h>

class Entity : public Ess3D::Object2D {
  public:
    Entity();
    Entity(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv);

    void interpolate(float timestepAccumulatorRatio) override;
    void resetInterpolation() override;

  protected:

};

#endif
