#ifndef TYPES_H_
#define TYPES_H_

/**
 * @author AndreaTgc (Andrea Colombo)
 * @date 02/15/25
 * @brief utility file containing common data types and related macros
 */

#include <stdint.h>

/**
 * We use typedefs for int types to enhance
 * readability, no other reason
 */
typedef uint64_t U64;
typedef uint32_t U32;
typedef uint16_t U16;
typedef uint8_t U8;

#define AS_BIT(i) (1ULL << (i))
#define CTOI(c) ((int)c - '0')

/**
 * Enum to recognise the different players
 */
typedef enum EColor
{
  BLACK,
  WHITE,
  COLOR_NB = 2
} Color;

/**
 * Enum to recognise the different piece types
 */
typedef enum EPieceType
{
  NO_PIECE_TYPE,
  PAWN,
  ROOK,
  KNIGHT,
  BISHOP,
  QUEEN,
  KING
} PieceType;

/**
 * Enum that represents the different pieces
 * found on the chess board
 */
typedef enum EPiece
{
  WHITE_PAWN = 0,
  WHITE_ROOK,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_QUEEN,
  WHITE_KING,
  BLACK_PAWN,
  BLACK_ROOK,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_QUEEN,
  BLACK_KING,
  PIECE_NB = 12
} Piece;

#define COLOR_FROM_PIECE(p) ((p) >= 6 ? BLACK : WHITE)

/**
 * This enum allows us to keep track of the
 * castling rights during the game, it effectively uses only
 * 4 bits -> BLACK_QS | BLACK_KS | WHITE_QS | WHITE_KS
 */
typedef enum ECastlingRights
{
  NO_CASTLING,
  WHITE_KS,
  WHITE_QS = WHITE_KS << 1,
  BLACK_KS = WHITE_KS << 2,
  BLACK_QS = WHITE_KS << 3,
  KING_SIDE = WHITE_KS | BLACK_QS,
  QUEEN_SIDE = WHITE_QS | BLACK_QS,
  WHITE_CASTLES = WHITE_KS | WHITE_QS,
  BLACK_CASTLES = BLACK_KS | BLACK_QS,
  ALL_CASTLES = WHITE_CASTLES | BLACK_CASTLES
} CastlingRights;

// clang-format off
typedef enum ESquare 
{
  A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
	NO_SQUARE,
	SQUARE_ZERO = A1,
	SQUARE_NB = 64,
} Square;
// clang-format on

#define IS_SQUARE_VALID(sq) ((sq) >= A1 && (sq) <= H8)
#define SQUARE_FROM_RF(r, f) ((int)(((r) * 8) + (f)))

#endif // TYPES_H_
