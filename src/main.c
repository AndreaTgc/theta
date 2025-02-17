#include "../include/tables.h"

int main(void)
{
  init_attack_boards();
  bb_print(knight_attacks[7]);
  bb_print(rook_attacks_mask(6));
  bb_print(get_rook_attacks(6, knight_attacks[7]));
}
