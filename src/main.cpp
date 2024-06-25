#include "alba.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main(int argc, char *argv[]) {
  std::cout << "Hello world!";

  SDL_Init(SDL_INIT_EVERYTHING);
  _window window(SDL_CreateWindow("Alba", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
                 SDL_DestroyWindow);

  _renderer renderer(SDL_CreateRenderer(window.get(), -1, 0),
                     SDL_DestroyRenderer);

  _surface board(SDL_LoadBMP("assets/board.bmp"), SDL_FreeSurface);
  _texture board_texture(
      SDL_CreateTextureFromSurface(renderer.get(), board.get()),
      SDL_DestroyTexture);
  _surface window_surface(SDL_GetWindowSurface(window.get()), SDL_FreeSurface);

  SDL_Event event;
  bool running = true;

  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      running = false;
    }

    SDL_RenderClear(renderer.get());
    SDL_RenderCopy(renderer.get(), board_texture.get(), NULL, NULL);
    SDL_RenderPresent(renderer.get());
  }

  board.reset();
  window_surface.reset();

  window.reset();
  renderer.reset();

  return 0;
}
