#ifndef __EVAL_H__
#define __EVAL_H__

#include <limits.h>
#define PLAYER  int
#define PLAYER1 1
#define PLAYER2 -1 
#define NOPLAYER 0
#define ERRORPLAYER   INT_MAX
#define BOOL    int
#define TRUE    1
#define FALSE   0

typedef struct State_struct
{
        PLAYER  field[3][3];
        PLAYER  current_player;
} State;
void initState(State *st);
void copyState(State src, State *dest);

typedef struct StateChain_struct
{
        State chain[10];
        int   len;
        int   val;
} StateChain;
void copyStateChain(StateChain src, StateChain *dest);
void appandStateToChain(State st, StateChain *chain);
void initStateChain(StateChain *chain);

void getBestChain(State current, StateChain chain, StateChain *res_chain);
BOOL getWinner(State current, PLAYER *result);
int getNext(State current, State next[]);

void prinsState(State st);
void prinsStates(State sts[], int len);
void printStateChain(StateChain chain);

#endif
