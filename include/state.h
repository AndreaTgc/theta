#ifndef STATE_H_
#define STATE_H_

#include "types.h"

/**
 * We represent the current game state as a collection of
 * bitboards and other game-related data.
 * we encode everything that's not a bitboard inside a 32-bits
 * integer, using the following pattern
 * BIT 0 -> 1 if white's turn, 0 if black's turn
 * BIT 1 to 4 -> Castling rights
 * BIT 5 to 8 -> En passant file
 * BIT 9 to 14 -> Moves since the last pawn move (50 moves rule)
 * BIT 15 to 31 -> Total moves
 */
typedef struct {
   U64 pieces[12];
   U64 wp;
   U64 bp;
   U32 metadata;
} State;

#define FREE_SQUARES(s) (~(s->bp | s->wp))
#define OCCUPIED_SQUARES(s) (s->bp | s->wp)

#define WHITE_TO_MOVE(s) (s->metadata & 1)
#define CASTLING_RIGHTS(s) ((s->metadata >> 1) & 0xF)
#define EN_PASSANT_FILE(s) ((s->metadata >> 5) & 0xF)
#define HALF_MOVE_CLOCK(s) ((s->metadata >> 9) & 0x3F)
#define TOTAL_MOVES(s) ((s->metadata >> 15) & 0x1FFFF)

#define SET_PLAYER_TO_MOVE(s, side) ((s)->metadata = ((s)->metadata & ~1U) | ((side) & 1U))

#define SET_CASTLING_RIGHTS(s, r)                                                                  \
   ((s)->metadata = ((s)->metadata & (~(0xF << 1))) | ((r & 0xF) << 1))

#define SET_EN_PASSANT_FILE(s, ep)                                                                 \
   ((s)->metadata = ((s)->metadata & (~(0xF << 5))) | ((ep & 0xF) << 5))

#define SET_HALF_MOVE_CLOCK(s, c)                                                                  \
   ((s)->metadata = ((s)->metadata & (~(0x3F << 9))) | ((c & 0x3F) << 9))

#define INCR_HALF_MOVE_CLOCK(s)                                                                    \
   ((s)->metadata = ((s)->metadata & (~(0x3F << 9))) | ((HALF_MOVE_CLOCK(s) & 0x3F) << 9))

#define SET_TOTAL_MOVES(s, t)                                                                      \
   ((s)->metadata = ((s)->metadata & ~(0x1FFFF << 15)) | ((t & 0x1FFFF) << 15))

#define INCR_TOTAL_MOVES(s)                                                                        \
   ((s)->metadata = ((s)->metadata & (~(0x1FFFF << 15))) | ((TOTAL_MOVES(s) & 0x1FFFF) << 15))

/**
 * prints the current state of the game
 */
void state_print(State *gs);

/**
 * Loads the entire game state from a fen string
 * including the board, player to move and other data
 */
void state_from_fen(State *gs, const char *fen);

#endif // STATE_H_
