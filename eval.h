#ifndef __EVAL_H__
#define __EVAL_H__

#define PLAYER  int
#define PLAYER1 1
#define PLAYER2 -1 
#define NOPLAYER 0
#define ERRORPLAYER   999
#define BOOL    int
#define TRUE    1
#define FALSE   0

typedef struct State_struct
{
        PLAYER  field[3][3];
        PLAYER  current_player;
} State;

PLAYER getWinner(State current);
int getNext(State current, State *next);
int getValueAndBestChain(State *state, State *chain, int *count);

#endif
