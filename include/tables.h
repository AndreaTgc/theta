#ifndef TABLES_H_
#define TABLES_H_

#include "bitboard.h"

/*--+--+--+--+--+--+--+--+--+--+*/
/*    FUNCTION DEFINITIONS      */
/*--+--+--+--+--+--+--+--+--+--+*/

void init_attack_boards(void);

static inline Bitboard pawn_attacks_mask(int square, Color player);
static inline Bitboard knight_attacks_mask(int square);
static inline Bitboard king_attacks_mask(int square);
static inline Bitboard bishop_attacks_mask(int square);
static inline Bitboard rook_attacks_mask(int square);

/*--+--+--+--+--+--+--+--+--+--+*/
/*  ATTACK AND MAGIC BITBOARDS  */
/*--+--+--+--+--+--+--+--+--+--+*/

extern Bitboard pawn_attacks[2][64];
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];
extern Bitboard rook_attacks[64][4096];
extern Bitboard bishop_attacks[64][512];

#endif // TABLES_H_
