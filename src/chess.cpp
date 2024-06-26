#include "chess.h"

#include <bitset>
#include <cctype>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

void Chessboard::setupBoard(std::string fen) {
  // 0 - board position
  // 1 -
  //
  int mode = 0;

  // meant for the board positions
  int rank = 0;
  int file = 0;

  for (char c : fen) {
    if (mode == 0) {
      if (c == '/') {
        rank++;
        file = 0;
        continue;
      }

      if (c == ' ') {
        mode++;
        continue;
      }

      bool is_lower = islower(c);
      char lowercase = tolower(c);
      u64 pos = 0b1;
      for (int i = 0; i < file + 8 * rank; i++) {
        pos <<= 1;
      }
      // u64 pos = 0b1 << (u64)(file + 8 * rank);

      if (std::isdigit(c)) {
        int a = std::atoi(&c);
        file += a;
      }

      if (file > 7) {
        file = 0;
        continue;
      }

      if (is_lower != 0) {
        blackPositions |= pos;
      } else {
        whitePositions |= pos;
      }

      allPositions |= pos;
      switch (lowercase) {
      case 'p':
        pawnPositions |= pos;
        break;
      case 'b':
        bishopPositions |= pos;
        break;
      case 'r':
        rookPositions |= pos;
        break;
      case 'n':
        knightPositions |= pos;
        break;
      case 'k':
        kingPositions |= pos;
        break;
      case 'q':
        queenPositions |= pos;
        break;
      default:
        break;
      }
      file++;
    }
  }

  return;
}
