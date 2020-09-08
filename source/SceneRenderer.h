#pragma once

#include <glm/glm.hpp>
#include <Ess3D/gl/Shader.h>
#include <Ess3D/2d/camera/Camera2D.h>
#include <Ess3D/2d/rendering/SpriteBatch.h>

class SceneRenderer {
  public:
    SceneRenderer();
    SceneRenderer(float _width, float _height);
    ~SceneRenderer();

    void render();
    Ess3D::Camera2D* getCamera();
    Ess3D::SpriteBatch* getSpriteBatch();

  private:
    Ess3D::Shader* _baseShader2D{};
    Ess3D::Camera2D* _camera{};
    Ess3D::SpriteBatch* _spriteBatch{};

    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    float _width{};
    float _height{};

};

