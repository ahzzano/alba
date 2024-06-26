#include "alba.h"
#include "types.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bitset>
#include <cmath>
#include <iostream>

_texture piecesTexture(nullptr, SDL_DestroyTexture);

void initializeTilemap(_renderer renderer) {
  _surface piecesSurface(SDL_LoadBMP("assets/pieces.bmp"), SDL_FreeSurface);
  piecesTexture.reset(
      SDL_CreateTextureFromSurface(renderer.get(), piecesSurface.get()));

  piecesSurface.reset();
}

void renderChessBoard(_renderer renderer, Chessboard &chessboard) {

  for (int i = 0; i < 64; i++) {
    u64 b = (u64)std::pow(2, i) & chessboard.allPositions;

    // if the cell is 0, we simply continue
    if (b == 0) {
      continue;
    }

    // check if the thing is the selected piece
    u64 is_selected = b & chessboard.selectedPiece & chessboard.allPositions;

    // some important information about the board
    u64 is_white = b & chessboard.whitePositions & chessboard.allPositions;
    u64 is_black = b & chessboard.blackPositions & chessboard.allPositions;

    u64 is_pawn = b & chessboard.pawnPositions & chessboard.allPositions;
    u64 is_rook = b & chessboard.rookPositions & chessboard.allPositions;
    u64 is_knight = b & chessboard.knightPositions & chessboard.allPositions;
    u64 is_bishop = b & chessboard.bishopPositions & chessboard.allPositions;
    u64 is_queen = b & chessboard.queenPositions & chessboard.allPositions;
    u64 is_king = b & chessboard.kingPositions & chessboard.allPositions;

    // create the dst rect
    int rank = i / 8;
    int file = i % 8;

    int xMouse, yMouse;
    SDL_Rect dstRect = {file * 125, rank * 125, 125, 125};

    if (is_selected != 0) {
      SDL_GetMouseState(&xMouse, &yMouse);
      dstRect = {xMouse - (125 / 2), yMouse - (125 / 2), 125, 125};
    }

    SDL_Rect srcRect{0, 0, 125, 125};

    if (is_black != 0) {
      srcRect.y += 125;
    }
    if (is_pawn > 0) {
      srcRect.x += 125 * 5;
    } else if (is_rook > 0) {
      srcRect.x += 125 * 4;
    } else if (is_knight > 0) {
      srcRect.x += 125 * 3;
    } else if (is_bishop > 0) {
      srcRect.x += 125 * 2;
    } else if (is_queen > 0) {
      srcRect.x += 125 * 1;
    } else if (is_king > 0) {
      srcRect.x = 0;
    }

    SDL_RenderCopy(renderer.get(), piecesTexture.get(), &srcRect, &dstRect);
  }
}
