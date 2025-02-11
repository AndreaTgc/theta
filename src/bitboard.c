#include "bitboard.h"
#include "macros.h"
#include <stdio.h>

void bb_print(bitboard_t b) {
  for (int r = 7; r >= 0; r--) {
    for (int f = 0; f < 8; f++) {
      bitboard_t mask = (AS_BIT((r * 8) + f));
      if (mask & b) {
        putchar('x');
      } else {
        putchar('.');
      }
      putchar(' ');
    }
    putchar('\n');
  }
  putchar('\n');
}
