#ifndef BITBOARD_H_
#define BITBOARD_H_

#include "macros.h"
#include <stdint.h>

typedef uint64_t bitboard_t;

// clang-format off
#define RANK_1 0x00000000000000FF
#define RANK_2 0x000000000000FF00
#define RANK_3 0x0000000000FF0000
#define RANK_4 0x00000000FF000000
#define RANK_5 0x000000FF00000000
#define RANK_6 0x0000FF0000000000
#define RANK_7 0x00FF000000000000
#define RANK_8 0xFF00000000000000
#define FILE_1 0x0101010101010101
#define FILE_2 0x0202020202020202
#define FILE_3 0x0404040404040404
#define FILE_4 0x0808080808080808
#define FILE_5 0x1010101010101010
#define FILE_6 0x2020202020202020
#define FILE_7 0x4040404040404040
#define FILE_8 0x8080808080808080

#define EMPTY_BITBOARD 0x0000000000000000
#define FULL_BITBOARD  0xFFFFFFFFFFFFFFFF
// clang-format on

#define BB_LSB(bb) (__builtin_ctzll(bb))
#define BB_MSB(bb) (__builtin_clzll(bb))

#define POP_LSB(bb, x)                                                         \
  x = BB_LSB(bb);                                                              \
  bb &= ~AS_BIT(x)

#define POP_MSB(bb, x)                                                         \
  x = BB_MSB(bb);                                                              \
  bb &= ~AS_BIT(x)

/**
 * Shows the current state of a bitboard by printing
 * 'X' on high bits and '.' on low ones
 */
void bb_print(bitboard_t b);

#endif // BITBOARD_H_
