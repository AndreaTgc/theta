#ifndef MOVEGEN_H_
#define MOVEGEN_H_

#include "bitboard.h"
#include "gamestate.h"
#include "move.h"

int gen_white_pawn_moves(state_t *gs, move_t *move_list, int start);
int gen_black_pawn_moves(state_t *gs, move_t *move_list, int start);

int gen_white_knight_moves(state_t *gs, move_t *move_list, int start);
int gen_black_knight_moves(state_t *gs, move_t *move_list, int start);

/**
 * Array containing the bitboards that define the possible knight
 * moves for every single square.
 * Knights "jump" on the board so we just need to check each possible
 * move for a single square avoiding the ones that lead to a square occupied
 * by a friendly piece.
 */
extern const bitboard_t KNIGHT_MOVES[64];

/**
 * Array containing the bitboards that define the possible bishop
 * moves for every single square
 */
extern const bitboard_t BISHOP_MOVES[64];

/**
 * Array containing the bitboards that define the possible rook
 * moves for every single square
 */
extern const bitboard_t ROOK_MOVES[64];

extern const bitboard_t BISHOP_MAGIC[64];
extern const bitboard_t ROOK_MAGIC[64];

#endif // MOVEGEN_H_
