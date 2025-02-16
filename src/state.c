#include "../include/state.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void state_print(State *gs)
{
  const char *pc = "PRNBQKprnbqk";
  printf("[PLAYER TO MOVE] %s\n", gs->player_to_move == WHITE ? "white" : "black");
  printf("[CASTLING RIGHTS] %d\n", gs->castling_rights);
  printf("[TOTAL MOVES] %d\n", gs->ply);
  printf("[HALF MOVE CLOCK] %d\n", gs->half_move_clock);
  putchar('\n');
  puts("+-+-+-+-+-+-+-+");
  int row = 7, col = 0;
  while (row >= 0)
  {
    while (col < 8)
    {
      char c = '.';
      for (int i = 0; i < PIECE_NB; i++)
      {
        if (gs->pieces[i] & AS_BIT(SQUARE_FROM_RF(row, col)))
        {
          c = pc[i];
          break;
        }
      }
      putchar(c);
      putchar(' ');
      col++;
    }
    putchar('\n');
    col = 0;
    row--;
  }
  puts("+-+-+-+-+-+-+-+");
}

void state_from_fen(State *gs, const char *fen)
{
  assert(gs && fen);
  memset(gs, 0, sizeof(State)); // Clear state structure
  const char *c = fen;
  int row = 7, col = 0;

  while (*c != ' ')
  {
    if (*c == '/')
    {
      row--; // Move to the next row
      col = 0;
    }
    else if (isdigit(*c))
    {
      col += CTOI(*c);
    }
    else
    {
      switch (*c)
      {
      case 'P':
        gs->pieces[WHITE_PAWN] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'R':
        gs->pieces[WHITE_ROOK] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'N':
        gs->pieces[WHITE_KNIGHT] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'B':
        gs->pieces[WHITE_BISHOP] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'Q':
        gs->pieces[WHITE_QUEEN] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'K':
        gs->pieces[WHITE_KING] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'p':
        gs->pieces[BLACK_PAWN] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'r':
        gs->pieces[BLACK_ROOK] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'n':
        gs->pieces[BLACK_KNIGHT] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'b':
        gs->pieces[BLACK_BISHOP] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'q':
        gs->pieces[BLACK_QUEEN] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      case 'k':
        gs->pieces[BLACK_KING] |= AS_BIT(SQUARE_FROM_RF(row, col));
        break;
      }
      col++;
    }
    c++;
  }
  compute_color_occupancies(gs);
  c++;
  gs->player_to_move = *c == 'w' ? WHITE : BLACK;
  c += 2;
  while (*c != ' ')
  {
    switch (*c)
    {
    case 'K':
      gs->castling_rights |= WHITE_KS;
      break;
    case 'Q':
      gs->castling_rights |= WHITE_QS;
      break;
    case 'k':
      gs->castling_rights |= BLACK_KS;
      break;
    case 'q':
      gs->castling_rights |= BLACK_QS;
      break;
    }
    c++;
  }
  c++;
}

inline void compute_color_occupancies(State *gs)
{
  gs->occupancies[WHITE] = gs->pieces[WHITE_PAWN] | gs->pieces[WHITE_ROOK] |
                           gs->pieces[WHITE_KNIGHT] | gs->pieces[WHITE_BISHOP] |
                           gs->pieces[WHITE_QUEEN] | gs->pieces[WHITE_KING];

  gs->occupancies[BLACK] = gs->pieces[BLACK_PAWN] | gs->pieces[BLACK_ROOK] |
                           gs->pieces[BLACK_KNIGHT] | gs->pieces[BLACK_QUEEN] |
                           gs->pieces[BLACK_KING];
}
