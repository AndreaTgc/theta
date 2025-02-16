#include "../include/tables.h"

/*--+--+--+--+--+--+--+--+--+--+*/
/*  ATTACK AND MAGIC BITBOARDS  */
/*--+--+--+--+--+--+--+--+--+--+*/

Bitboard pawn_attacks[2][64];
Bitboard knight_attacks[64];
Bitboard king_attacks[64];
Bitboard rook_attacks[64][4096];
Bitboard bishop_attacks[64][512];

/*--+--+--+--+--+--+--+--+--+--+*/
/*   FUNCTION IMPLEMENTATIONS   */
/*--+--+--+--+--+--+--+--+--+--+*/

void init_attack_boards(void)
{
  for (int i = 0; i < SQUARE_NB; i++)
  {
    pawn_attacks[WHITE][i] = pawn_attacks_mask(i, WHITE);
    pawn_attacks[BLACK][i] = pawn_attacks_mask(i, BLACK);
    knight_attacks[i] = knight_attacks_mask(i);
    king_attacks[i] = king_attacks_mask(i);
  }
}

static inline Bitboard pawn_attacks_mask(int square, Color player)
{
  Bitboard attacks = EMPTY_BITBOARD;
  if (player == WHITE)
  {
    if (AS_BIT(square) & ~FILE_8)
      attacks |= AS_BIT(square) << 9;
    if (AS_BIT(square) & ~FILE_1)
      attacks |= AS_BIT(square) << 7;
  }
  else
  {
    if (AS_BIT(square) & ~FILE_1)
      attacks |= AS_BIT(square) >> 7;
    if (AS_BIT(square) & ~FILE_8)
      attacks |= AS_BIT(square) >> 9;
  }
  return attacks;
}

static inline Bitboard knight_attacks_mask(int square)
{
  Bitboard attacks = EMPTY_BITBOARD;
  if (AS_BIT(square) >> 17 & ~FILE_8)
    attacks |= AS_BIT(square) >> 17;
  if (AS_BIT(square) >> 15 & ~FILE_1)
    attacks |= AS_BIT(square) >> 15;
  if (AS_BIT(square) >> 10 & ~(FILE_7 | FILE_8))
    attacks |= AS_BIT(square) >> 10;
  if (AS_BIT(square) >> 6 & ~(FILE_1 | FILE_2))
    attacks |= AS_BIT(square) >> 6;
  if (AS_BIT(square) << 17 & ~FILE_1)
    attacks |= AS_BIT(square) << 17;
  if (AS_BIT(square) << 15 & ~FILE_8)
    attacks |= AS_BIT(square) << 15;
  if (AS_BIT(square) << 10 & ~(FILE_1 | FILE_2))
    attacks |= AS_BIT(square) << 10;
  if (AS_BIT(square) << 6 & ~(FILE_8 | FILE_7))
    attacks |= AS_BIT(square) << 6;
  return attacks;
}

static inline Bitboard king_attacks_mask(int square)
{
  Bitboard attacks = EMPTY_BITBOARD;
  if (AS_BIT(square) & ~FILE_1)
  {
    attacks |= AS_BIT(square) >> 1;
    attacks |= AS_BIT(square) << 7;
    attacks |= AS_BIT(square) >> 9;
  }
  if (AS_BIT(square) & ~FILE_8)
  {
    attacks |= AS_BIT(square) << 1;
    attacks |= AS_BIT(square) << 9;
    attacks |= AS_BIT(square) >> 7;
  }
  attacks |= AS_BIT(square) << 8;
  attacks |= AS_BIT(square) >> 8;
  return attacks;
}

static inline Bitboard bishop_attacks_mask(int square)
{
  Bitboard attacks = EMPTY_BITBOARD;
  int rk, fl;
  int rank = square / 8;
  int file = square % 8;
  for (rk = rank + 1, fl = file + 1; rk <= 7 && fl <= 7; rk++, fl++)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank - 1, fl = file + 1; rk >= 0 && fl <= 7; rk--, fl++)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank + 1, fl = file - 1; rk <= 7 && fl >= 0; rk++, fl--)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank - 1, fl = file - 1; rk >= 0 && fl >= 0; rk--, fl--)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  return attacks;
}

static inline Bitboard rook_attacks_mask(int square)
{
  Bitboard attacks = EMPTY_BITBOARD;
  int rank = square / 8;
  int file = square % 8;
  int rk, fl;
  for (rk = rank + 1, fl = file; rk <= 7; rk++)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank - 1, fl = file; rk >= 0; rk--)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank, fl = file + 1; fl <= 8; fl++)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  for (rk = rank, fl = file - 1; fl >= 0; fl--)
    attacks |= AS_BIT(SQUARE_FROM_RF(rk, fl));
  return attacks;
}
