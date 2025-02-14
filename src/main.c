#include "../include/state.h"
#include "../include/bitboard.h"

int main(void)
{
   State gs = {0};
   state_from_fen(&gs, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
   state_print(&gs);
   for (U64 i = 0; i < 12; i++)
   {
      bb_print(gs.pieces[i]);
   }
}
