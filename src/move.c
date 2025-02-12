#include "../include/move.h"
#include <stdio.h>

#define FILE_FROM_SQ(sq) (('a') + ((sq) % 8))
#define RANK_FROM_SQ(sq) (('1') + ((sq) / 8))

void move_print(move_t m)
{
  int from = MOVE_GET_FROM(m);
  int to   = MOVE_GET_TO(m);
  int flag = MOVE_GET_FLAG(m);
  int i    = 0;
  if ( flag == QS_CASTLE )
  {
    puts("O--O");
    return;
  }
  if ( flag == KS_CASTLE )
  {
    puts("O-O");
    return;
  }
  char s[7];
  s[i++] = FILE_FROM_SQ(from);
  s[i++] = RANK_FROM_SQ(from);
  if ( MOVE_IS_CAPTURE(m) )
  {
    s[i++] = 'x';
  }
  s[i++] = FILE_FROM_SQ(to);
  s[i++] = RANK_FROM_SQ(to);
  if ( MOVE_IS_PROMOTION(m) )
  {
    switch ( flag )
    {
    case PROMO_QUEEN:
      s[i++] = 'Q';
      break;
    case PROMO_ROOK:
      s[i++] = 'R';
      break;
    case PROMO_KNIGHT:
      s[i++] = 'N';
      break;
    case PROMO_BISHOP:
      s[i++] = 'B';
      break;
    default:
      ASSERT(0, "Unreachable case in move parsing");
      break;
    }
    s[i++] = '\0';
  }
  else
    s[i++] = '\0';
  puts(s);
}

void move_apply(state_t *gs, move_t m)
{
  int         from = MOVE_GET_FROM(m);
  int         to   = MOVE_GET_TO(m);
  bitboard_t *fbb  = NULL;
  for ( int i = 0; i < 12; i++ )
  {
    if ( AS_BIT(from) & gs->pieces[i] )
    {
      fbb = &gs->pieces[i];
      break;
    }
  }
  ASSERT(fbb, "Move starting square wasn't occupied by a piece\n");
  *fbb &= ~(AS_BIT(from));
  if ( MOVE_IS_CAPTURE(m) )
  {
    bitboard_t *tbb = NULL;
    for ( int i = 0; i < 12; i++ )
    {
      if ( AS_BIT(to) & gs->pieces[i] )
      {
        tbb = &gs->pieces[i];
        break;
      }
    }
    ASSERT(tbb, "Move 'to' square for capture wasn't occupied\n");
    *tbb &= ~(AS_BIT(to));
  }
  if ( MOVE_IS_PROMOTION(m) )
  {
    switch ( MOVE_GET_FLAG(m) )
    {
    case PROMO_QUEEN:
      if ( AS_BIT(to) & RANK_1 )
      {
        gs->pieces[10] |= (AS_BIT(to));
      }
      else
      {
        gs->pieces[4] |= (AS_BIT(to));
      }
      break;
    case PROMO_BISHOP:
      if ( AS_BIT(to) & RANK_1 )
      {
        gs->pieces[9] |= (AS_BIT(to));
      }
      else
      {
        gs->pieces[3] |= (AS_BIT(to));
      }
      break;
    case PROMO_ROOK:
      if ( AS_BIT(to) & RANK_1 )
      {
        gs->pieces[7] |= (AS_BIT(to));
      }
      else
      {
        gs->pieces[1] |= (AS_BIT(to));
      }
      break;
    case PROMO_KNIGHT:
      if ( AS_BIT(to) & RANK_1 )
      {
        gs->pieces[8] |= (AS_BIT(to));
      }
      else
      {
        gs->pieces[2] |= (AS_BIT(to));
      }
      break;
    default:
      ASSERT(0, "Unreachable case in move application");
      break;
    }
  }
  else
  {
    *fbb |= (AS_BIT(to));
  }
}
