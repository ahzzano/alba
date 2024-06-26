#include <SDL2/SDL_render.h>
#define SDL_MAIN_HANDLED

#include "albarenderer.h"
#include "types.h"

void initializeTilemap(_renderer renderer);
void renderChessBoard(_renderer renderer, Chessboard &chessboard);
