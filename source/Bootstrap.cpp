#define _CRTDBG_MAP_ALLOC

#include <SDL2/SDL.h>
#include <Ess3D/errors/RuntimeException.h>
#include "Game.h"

int main(int argc, char* args[]) {
  Game* game = Game::GetInstance();

  try {
    game->boot();
    game->run();
    game->destroy();
  } catch (Ess3D::ERuntimeException& anException) {
    std::cout << anException.getMessage() << std::endl;
  }

  return 0;
}
