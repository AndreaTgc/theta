#include "../include/bitboard.h"
#include <stdio.h>

void bb_print(Bitboard b)
{
  puts("+-+-+-+-+-+-+-+");
  for (int i = 0; i < 64; i++)
  {
    int r = 7 - (i / 8); // Reverse rank (since boards are printed top-down)
    int f = i % 8;       // File remains unchanged

    putchar((AS_BIT((r * 8) + f) & b) ? 'x' : '.');
    putchar((f == 7) ? '\n' : ' '); // New line after every 8 squares
  }
  puts("+-+-+-+-+-+-+-+");
  putchar('\n');
}

U64 bb_pop_lsb(Bitboard *b)
{
  U64 r = BB_LSB(*b);
  *b &= ~r;
  return r;
}

U64 bb_pop_msb(Bitboard *b)
{
  U64 r = BB_MSB(*b);
  *b &= ~r;
  return r;
}
