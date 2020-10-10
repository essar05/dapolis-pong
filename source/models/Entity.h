#ifndef DAPOLIS_PONG_ENTITY_H
#define DAPOLIS_PONG_ENTITY_H

#include <Ess3D/2d/models/Object2D.h>
#include <box2d/box2d.h>
#include <memory>
#include <string>

class Entity : public Ess3D::Object2D {
  public:
    Entity();
    Entity(const glm::vec2& position, const glm::vec2& size, GLuint textureId, const glm::vec4& uv, std::string id);

    void interpolate(float timestepAccumulatorRatio) override;
    void resetInterpolation() override;

    b2Body* getBody();
    std::string getId();
    bool hasId(std::string id);

    virtual void initializePhysicsBody(b2World* world);

  protected:
    std::string _id;
    b2Body* _body;

    virtual void initializeBody(b2World* world)= 0;
    virtual void initializeFixtures(b2World* world) = 0;
};

#endif
