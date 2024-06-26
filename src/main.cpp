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
  std::cout << "Hello world!\n";

  SDL_Init(SDL_INIT_EVERYTHING);
  _window window(SDL_CreateWindow("Alba", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN),
                 SDL_DestroyWindow);

  _renderer renderer(SDL_CreateRenderer(window.get(), -1, 0),
                     SDL_DestroyRenderer);

  _surface boardbg(SDL_LoadBMP("assets/board.bmp"), SDL_FreeSurface);
  _texture boardTexture(
      SDL_CreateTextureFromSurface(renderer.get(), boardbg.get()),
      SDL_DestroyTexture);
  _surface window_surface(SDL_GetWindowSurface(window.get()), SDL_FreeSurface);

  SDL_Event event;
  bool running = true;

  initializeTilemap(renderer);

  Chessboard board;
  board.setupBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
      running = false;
    }

    SDL_RenderClear(renderer.get());
    SDL_RenderCopy(renderer.get(), boardTexture.get(), NULL, NULL);
    renderChessBoard(renderer, board);
    SDL_RenderPresent(renderer.get());
  }

  boardbg.reset();
  window_surface.reset();

  window.reset();
  renderer.reset();

  return 0;
}
