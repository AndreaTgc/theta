#ifndef MOVE_H_
#define MOVE_H_

#include "gamestate.h"
#include "macros.h"
#include <stdint.h>

/**
 * We can encode moves in a single 16-bits integer by
 * using the following format:
 * 6 bits for the starting square
 * 6 bits for the end square
 * 4 bits to keep track of the move type
 *
 * 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 * |---------| |------------| |-----------|
 *    FLAG          TO-SQ         FROM-SQ
 */
typedef uint16_t move_t;

// clang-format off
#define NORMAL_MOVE  0x0 // 0000
#define KS_CASTLE    0x1 // 0001
#define QS_CASTLE    0x2 // 0010
#define DOUBLE_PAWN  0x3 // 0011
#define CAPTURE      0x4 // 0100
#define EN_PASSANT   0x5 // 0101
#define PROMO_QUEEN  0x8 // 1000
#define PROMO_ROOK   0x9 // 1001
#define PROMO_KNIGHT 0xA // 1010
#define PROMO_BISHOP 0xB // 1011
#define PC_QUEEN     0xC // 1100
#define PC_ROOK      0xD // 1101
#define PC_KNIGHT    0xE // 1110
#define PC_BISHOP    0xF // 1111
// clang-format on

#define MOVE(from, to, flag) CAST(move_t, ((from) | (to << 6) | (flag << 12)))

#define MOVE_GET_FROM(move) (move & 0x3F)
#define MOVE_GET_TO(move) (move >> 6 & 0x3F)
#define MOVE_GET_FLAG(move) (move >> 12 & 0xF)

#define MOVE_IS_PROMOTION(move) ((MOVE_GET_FLAG(move)) & PROMO_QUEEN)
#define MOVE_IS_CAPTURE(move) ((MOVE_GET_FLAG(move)) & CAPTURE)

#define MOVE_SET_FROM(move, f)                                                 \
  do {                                                                         \
    (move) &= ~0x3F;                                                           \
    (move) |= (f & 0x3F);                                                      \
  } while (0)

#define MOVE_SET_TO(move, t)                                                   \
  do {                                                                         \
    (move) &= ~0xFC0;                                                          \
    (move) |= ((t & 0x3F) << 6);                                               \
  } while (0)

#define MOVE_SET_FLAG(move, f)                                                 \
  do {                                                                         \
    (move) &= ~0xF;                                                            \
    (move) |= ((f & 0xF) << 12);

void move_print(move_t m);

void move_apply(state_t *gs, move_t m);

void move_undo(state_t *gs, move_t m);

#endif // MOVE_H_
