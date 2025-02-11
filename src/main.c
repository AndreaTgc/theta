#include "gamestate.h"
#include "movegen.h"

int main() {
  state_t gs;
  const char *fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  state_from_fen(&gs, fen);
  for (int i = 0; i < 64; i++) {
    bb_print(KNIGHT_MOVES[i]);
  }
}
