#include <stdio.h>
#include "eval.h"
#include "io.h"


BOOL goNext2Turn(State in, State *out, BOOL isPlayer1Human, BOOL isPlayer2Human)
{
        BOOL res = FALSE;
        PLAYER winner;
        State tmp;
        if (isPlayer1Human)
        {
                printState(in);
                res = askTurn(in, &tmp);
        
        } else
                res = calcTurn(in, &tmp);
        if (!res || getWinner(tmp, &winner))
        {
                copyState(tmp, out);
                return FALSE;
        }

        if (isPlayer2Human)
        {
                printState(tmp);
                res = askTurn(tmp, out);
        } else
                res = calcTurn(tmp, out);
        if (!res || getWinner(*out, &winner))
                return FALSE;
        return TRUE;
}

void runGameCycle(BOOL isP1Human, BOOL isP2Human)
{
        State st1; State st2;
        initState(&st1); initState(&st2);

        while (goNext2Turn(st1, &st2, isP1Human, isP2Human))
                swapState(&st1, &st2);   
        printState(st2);
}

void main()
{
        runGameCycle(FALSE, TRUE);
}
