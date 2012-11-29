#ifndef __EVAL_H__
#define __EVAL_H__

#include <limits.h>
#define PLAYER  int
#define PLAYER1 1
#define PLAYER2 -1 
#define NOPLAYER 0
#define ERRORPLAYER   INT_MAX
#define NAN   INT_MIN
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
BOOL compareStates(State st1, State st2);
void swapState(State *st1, State *st2);

typedef struct StateChain_struct
{
        State chain[10];
        int   len;
        int   val;
} StateChain;
State getStateChainTop(const StateChain *chain);
void copyStateChain(StateChain src, StateChain *dest);
void appandStateToChain(State st, StateChain *chain);
void initStateChain(StateChain *chain);

void getBestChain(State current, StateChain *res_chain);
BOOL getWinner(State current, PLAYER *result);
int getNext(State current, State next[]);
PLAYER switchPlayer(State state);

BOOL calcTurn(State in, State *out);
#endif
