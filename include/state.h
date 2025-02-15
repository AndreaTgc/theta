#ifndef STATE_H_
#define STATE_H_

#include "types.h"
#include "bitboard.h"

/**
 * We represent the current game state as a collection of
 * bitboards and other game-related data.
 */
typedef struct
{
  Bitboard pieces[PIECE_NB];
  Bitboard occupancies[COLOR_NB];
  U64 zobrist_key;
  Square ep_square;
  Color player_to_move;
  CastlingRights castling_rights;
  U16 ply;
  U16 half_move_clock;
} State;

#define INIT_FEN_STR "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define INIT_STATE(gs) state_from_fen(gs, INIT_FEN_STR)

/**
 * prints the current state of the game
 */
void state_print(State *gs);

/**
 * Loads the entire game state from a fen string
 * including the board, player to move and other data
 */
void state_from_fen(State *gs, const char *fen);

/**
 * Returns the fen string that represents the current
 * game state
 * @note The caller is responsible for deallocating the string
 * after using it to avoid leaking memory
 */
char *state_as_fen(State *gs);

/**
 * Recomputes the players occupancies by using bitwise OR
 * over the pieces' bitboards
 */
inline void compute_color_occupancies(State *gs);

#endif // STATE_H_
