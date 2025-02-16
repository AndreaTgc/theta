#include "../include/tables.h"

int main(void)
{
  init_attack_boards();
  for (int i = 0; i < 64; i++)
  {
    bb_print(rook_attacks[i][0]);
  }
}
