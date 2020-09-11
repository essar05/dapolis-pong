#include "SceneRenderer.h"
#include "Game.h"
#include <glm/gtc/type_ptr.hpp>

SceneRenderer::SceneRenderer() = default;

SceneRenderer::SceneRenderer(float _width, float _height) {
  this->_width = _width;
  this->_height = _height;

  _baseShader2D = new Ess3D::Shader(true);

  _baseShader2D->loadShader(Ess3D::ShaderType::VERTEX, "Shaders/2D.vs");
  _baseShader2D->loadShader(Ess3D::ShaderType::FRAGMENT, "Shaders/2D.fs");
  _baseShader2D->compileShaders();

  _baseShader2D->addAttribute("vertexPosition");
  _baseShader2D->addAttribute("vertexColor");
  _baseShader2D->addAttribute("vertexUV");

  _baseShader2D->linkShaders();

  _camera = new Ess3D::Camera2D();

  _camera->init((int) this->_width, (int) this->_height, 50.f);
  _camera->setZoom(1.0f);
  _camera->setPosition(glm::vec2(0.0f, 0.0f));

  _spriteBatch = new Ess3D::SpriteBatch();
  _spriteBatch->init();

  glEnable(GL_DEPTH_TEST);
}

SceneRenderer::~SceneRenderer() {
  delete _baseShader2D;
  delete _camera;
  delete _spriteBatch;
}

void SceneRenderer::render() {
  Game* game = Game::GetInstance();

  glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _baseShader2D->use();

  glActiveTexture(GL_TEXTURE0);
  GLint textureLocation = _baseShader2D->getUniformLocation("textureSampler");
  glUniform1i(textureLocation, 0);

  GLint useTextureLocation = _baseShader2D->getUniformLocation("useTexture");
  glUniform1i(useTextureLocation, 1);

  GLint pLocation = _baseShader2D->getUniformLocation("P");
  glm::mat4 cameraMatrix = _camera->getCameraMatrix();

  glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

  _spriteBatch->begin(Ess3D::GlyphSortType::BACK_TO_FRONT);

  // render the scene
  game->getGameplayScreen()->getBall()->draw();

  _spriteBatch->end();
  _spriteBatch->render();

  glUniform1i(useTextureLocation, 0);

  _baseShader2D->unuse();
}

Ess3D::Camera2D* SceneRenderer::getCamera() {
  return this->_camera;
}

Ess3D::SpriteBatch *SceneRenderer::getSpriteBatch() {
  return this->_spriteBatch;
}
