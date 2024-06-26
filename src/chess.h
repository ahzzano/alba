#include "types.h"
#include <string>

class Chessboard {
public:
  // We will be using bit boards to make this very efficient
  // Especially when were doing make-unmake moves later
  u64 allPositions = 0;

  /* the board is represented using the following
   * *----*----*----*----*----*----*----*----*
   * | a0 | a1 | a2 | a3 | a4 | a5 | a6 | a7|
   * *----*----*----*----*----*----*----*----*
   * | a8 | a9 |a10| a11| a12| a13| a14| a15|
   * *----*----*----*----*----*----*----*----*
   * ...
   * yes you get the gist
   */

  // we will be using this
  u64 selectedPiece = 0;

  // Positions of each side
  u64 whitePositions = 0;
  u64 blackPositions = 0;

  // Positions of each piece
  // If we want to get the positions of the white bishops,
  // we simply use a bitwise OR operation on whitePositions and bishopPositions
  u64 pawnPositions = 0;
  u64 rookPositions = 0;
  u64 bishopPositions = 0;
  u64 knightPositions = 0;
  u64 queenPositions = 0;
  u64 kingPositions = 0;

  // we effectively store 9 u64 integers rather than having 64 32-bit integers
  // in an array
  //
  // we can simply use bitwise operations rather than looping!

  bool whiteTurn = true;

  /**
   * @brief this function setups the 9 different bitboards for the board
   * @param fen this will take in a FEN string that will setup the states
   */
  void setupBoard(std::string fen);
};
