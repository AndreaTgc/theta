#include "../include/state.h"

inline void recompute_player_occupancies(State *gs)
{
  gs->occupancies[WHITE] = gs->pieces[WHITE_PAWN] | gs->pieces[WHITE_ROOK] |
                           gs->pieces[WHITE_KNIGHT] | gs->pieces[WHITE_BISHOP] |
                           gs->pieces[WHITE_QUEEN] | gs->pieces[WHITE_KING];

  gs->occupancies[BLACK] = gs->pieces[BLACK_PAWN] | gs->pieces[BLACK_ROOK] |
                           gs->pieces[BLACK_KNIGHT] | gs->pieces[BLACK_QUEEN] |
                           gs->pieces[BLACK_KING];
}