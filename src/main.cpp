#include "alba.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[]) {
  std::cout << "Hello world!";

  SDL_Init(SDL_INIT_EVERYTHING);
  _window window(SDL_CreateWindow("Alba", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
                 SDL_DestroyWindow);

  _renderer renderer(SDL_CreateRenderer(window.get(), -1, 0),
                     SDL_DestroyRenderer);

  SDL_Event event;
  bool running = true;

  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      running = false;
    }
  }

  return 0;
}
