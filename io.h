#ifndef __IO_H__
#define __IO_H__

#include "eval.h"

void prinsState(State st);
void prinsStates(State sts[], int len);
void printStateChain(StateChain chain);
BOOL askTurn(State in, State *out);
char* getPlayerSign(PLAYER p);

#endif
