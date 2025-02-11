#include "gamestate.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void state_print(state_t *gs)
{
  const char *ps = "PRNBQKprnbqk";
  for ( int rank = 7; rank >= 0; rank-- )
  {
    for ( int file = 0; file < 8; file++ )
    {
      int  square = rank * 8 + file;
      char piece  = '.';
      for ( int i = 0; i < 12; i++ )
      {
        if ( gs->pieces[i] & (1ULL << square) )
        {
          piece = ps[i];
          break;
        }
      }
      putchar(piece);
      putchar(' ');
    }
    putchar('\n');
  }
  printf("Player to move: %s\n", WHITE_TO_MOVE(gs) ? "White" : "Black");
  printf("Castling: %s\n", CASTLING_RIGHTS(gs) ? "Yes" : "No");
  printf("En Passant: %d\n", EN_PASSANT_FILE(gs) != 0xF ? EN_PASSANT_FILE(gs) : '-');
  printf("Half-move clock: %d\n", HALF_MOVE_CLOCK(gs));
  printf("Full-move number: %d\n", TOTAL_MOVES(gs));
}

void state_from_fen(state_t *gs, const char *fen)
{
  memset(gs, 0, sizeof(state_t));
  const char *ps     = "PRNBQKprnbqk";
  int         square = 56;
  const char *c      = fen;
  while ( *c && *c != ' ' )
  {
    if ( *c == '/' )
    {
      square -= 16;
    }
    else if ( isdigit(*c) )
    {
      square += (*c - '0');
    }
    else
    {
      for ( int i = 0; i < 12; i++ )
      {
        if ( *c == ps[i] )
        {
          gs->pieces[i] |= (1ULL << square);
          break;
        }
      }
      square++;
    }
    c++;
  }
  c++;
  if ( *c == 'w' )
  {
    SET_PLAYER_TO_MOVE(gs, 1);
  }
  else if ( *c == 'b' )
  {
    SET_PLAYER_TO_MOVE(gs, 0);
  }
  c++;
  c++;
  int castles = 0;
  if ( *c != '-' )
  {
    while ( *c != ' ' && *c != '\0' )
    {
      if ( *c == 'K' )
        castles |= 0b1000; // White kingside
      if ( *c == 'Q' )
        castles |= 0b0100; // White queenside
      if ( *c == 'k' )
        castles |= 0b0010; // Black kingside
      if ( *c == 'q' )
        castles |= 0b0001; // Black queenside
      c++;
    }
  }
  SET_CASTLING_RIGHTS(gs, castles);
  c++;
  if ( *c != '-' )
  {
    if ( *c >= 'a' && *c <= 'h' )
    {
      int ep = (*c - 'a');
      SET_EN_PASSANT_FILE(gs, ep);
    }
    else
    {
      SET_EN_PASSANT_FILE(gs, 0xF);
    }
  }
  else
  {
    SET_EN_PASSANT_FILE(gs, 0xF);
  }
  c += 2;
  char n[5];
  int  i = 0;
  while ( isdigit(*c) )
  {
    n[i++] = *c;
    c++;
  }
  n[i] = '\0';
  SET_HALF_MOVE_CLOCK(gs, atoi(n));
  c++;
  i = 0;
  while ( isdigit(*c) )
  {
    n[i++] = *c;
    c++;
  }
  n[i] = '\0';
  SET_TOTAL_MOVES(gs, atoi(n));
  for ( int i = 0; i < 6; i++ )
  {
    gs->wp |= gs->pieces[i];
  }
  for ( int i = 6; i < 12; i++ )
  {
    gs->bp |= gs->pieces[i];
  }
}
