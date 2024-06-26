#include "chess.h"

#include <cctype>
#include <csignal>
#include <cstdlib>
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
      u64 pos = 1ull << (file + 8 * rank);

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

ChessPiece Chessboard::getPieceOnPosition(u64 position) {
  if ((position & pawnPositions) != 0) {
    return ChessPiece::Pawn;
  } else if ((position & rookPositions) != 0) {
    return ChessPiece::Rook;
  } else if ((position & bishopPositions) != 0) {
    return ChessPiece::Bishop;
  } else if ((position & knightPositions) != 0) {
    return ChessPiece::Knight;
  } else if ((position & queenPositions) != 0) {
    return ChessPiece::Queen;
  } else {
    return ChessPiece::King;
  }
}

bool Chessboard::isBlack(u64 position) {
  return (blackPositions & position) > 0;
}

void moveBit(u64 *board, u64 currentPosition, u64 newPosition) {
  *board ^= currentPosition;
  *board |= newPosition;
}

u64 moveBit(u64 board, u64 currentPosition, u64 newPosition) {
  u64 toRet = board;
  toRet ^= currentPosition;
  toRet |= newPosition;
  return toRet;
}

void Chessboard::makeMove(int targetPiece) {
  u64 targetPieceInBits = 1ull << targetPiece;

  allPositions ^= selectedPiece;
  allPositions |= targetPieceInBits;

  // TODO: Make sure that the piece gets consumed rather than overlaps being
  // present over two different bitboards
  //
  if ((selectedPiece & blackPositions) > 0) {
    blackPositions ^= selectedPiece;
    blackPositions |= targetPieceInBits;
  }

  switch (getPieceOnPosition(selectedPiece)) {
  case ChessPiece::Pawn: {
    pawnPositions ^= selectedPiece;
    pawnPositions |= targetPieceInBits;
    break;
  }
  case ChessPiece::Rook: {
    rookPositions ^= selectedPiece;
    rookPositions |= targetPieceInBits;
    break;
  }
  case ChessPiece::Bishop: {
    bishopPositions ^= selectedPiece;
    bishopPositions |= targetPieceInBits;
    break;
  }
  case ChessPiece::Knight: {
    knightPositions ^= selectedPiece;
    knightPositions |= targetPieceInBits;
    break;
  }
  case ChessPiece::King: {
    kingPositions ^= selectedPiece;
    kingPositions |= targetPieceInBits;
    break;
  }
  case ChessPiece::Queen: {
    queenPositions ^= selectedPiece;
    queenPositions |= targetPieceInBits;
    break;
  }
  default:
    break;
  }

  selectedPiece = 0;
}
