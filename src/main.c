#include "../include/gamestate.h"
#include "../include/movegen.h"

int main(void)
{
  state_t gs;
  // const char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0
  // 1";
  const char *fen = "8/8/8/8/pppppppp/5N2/8/8 w KQkq - 0 1";
  state_from_fen(&gs, fen);
  state_print(&gs);
  move_t moves[256];
  int    i = gen_white_knight_moves(&gs, moves, 0);
  for ( int k = 0; k < i; k++ )
  {
    move_print(moves[k]);
  }
}
