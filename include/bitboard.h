#ifndef BITBOARD_H_
#define BITBOARD_H_

#include "types.h"

/**
 * Since the chess board is a 8x8 matrix, we can represent
 * the board using a 64-bits integer, this allows us to use
 * bit operations (incredibly fast on modern CPUs) to manipulate
 * these boards
 */
typedef U64 Bitboard;

// clang-format off
#define RANK_1 0x00000000000000FF
#define RANK_2 0x000000000000FF00
#define RANK_3 0x0000000000FF0000
#define RANK_4 0x00000000FF000000
#define RANK_5 0x000000FF00000000
#define RANK_6 0x0000FF0000000000
#define RANK_7 0x00FF000000000000
#define RANK_8 0xFF00000000000000
#define FILE_A 0x0101010101010101
#define FILE_B 0x0202020202020202
#define FILE_C 0x0404040404040404
#define FILE_D 0x0808080808080808
#define FILE_E 0x1010101010101010
#define FILE_F 0x2020202020202020
#define FILE_G 0x4040404040404040
#define FILE_H 0x8080808080808080

#define EMPTY_BITBOARD 0x0000000000000000
#define FULL_BITBOARD  0xFFFFFFFFFFFFFFFF
// clang-format on

#define BB_LSB(bb) (__builtin_ctzll(bb))
#define BB_MSB(bb) (__builtin_clzll(bb))
#define BB_BITCOUNT(bb) (__builtin_popcountll(bb))

/*--+--+--+--+--+--+--+--+--+--+*/
/*    FUNCTION DEFINITIONS      */
/*--+--+--+--+--+--+--+--+--+--+*/

/**
 * Shows the current state of a bitboard by printing
 * 'X' on high bits and '.' on low ones
 */
void bb_print(Bitboard b);

U64 bb_pop_lsb(Bitboard *b);
U64 bb_pop_msb(Bitboard *b);

#endif // BITBOARD_H_
