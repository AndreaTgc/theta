#ifndef TABLES_H_
#define TABLES_H_

#include "bitboard.h"

/*--+--+--+--+--+--+--+--+--+--+*/
/*    FUNCTION DEFINITIONS      */
/*--+--+--+--+--+--+--+--+--+--+*/

// Computes all the attack and magic bitboards
// when the engine starts
void init_attack_boards(void);

// Generates the possible captures for pawns from a given square
Bitboard pawn_attacks_mask(int square, Color player);

// Generates all possible moves for a knight in a given square
Bitboard knight_attacks_mask(int square);

// Generates all possible moves for a king in a given square
Bitboard king_attacks_mask(int square);

// Generates the relevant mask for bishops (magic bitboard comp)
// this function assumes there are no blockers
Bitboard bishop_attacks_mask(int square);

// Generates the mask for possible bishop attacks given a set of
// blocking pieces on the board
Bitboard get_bishop_attacks(int square, Bitboard blocks);

// Generates the relevant mask for rooks (magic bitboard comp)
// this function assumes there are no blockers
Bitboard rook_attacks_mask(int square);

// Generates the mask for possible rook attacks given a set of
// blocking pieces on the board
Bitboard get_rook_attacks(int square, Bitboard blocks);

/*--+--+--+--+--+--+--+--+--+--+*/
/*  ATTACK AND MAGIC BITBOARDS  */
/*--+--+--+--+--+--+--+--+--+--+*/

extern Bitboard pawn_attacks[2][64];
extern Bitboard knight_attacks[64];
extern Bitboard king_attacks[64];
extern Bitboard rook_attacks[64][4096];
extern Bitboard bishop_attacks[64][512];

extern U64 rook_magic[64];
extern int rook_m_shifts[64];
extern U64 bishop_magic[64];
extern int bishop_m_shifts[64];

#endif // TABLES_H_
