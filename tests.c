#include "eval.h"
#include "tests.h"
#include <stdio.h>
#include "assert.h"

void runTests()
{
        nextTest();
        getWinnerTest();
        getBestChainTest();
}

void nextTest()
{
        State st;
        initState(&st);
        State sts[10];
        int count = getNext(st, sts);
        assert(count == 9);

        int i, j;
        for (i = 0; i < count; ++i)
                for (j = i+1; j < count; ++j)
                        assert(!compareStates(sts[i], sts[j]));
}

void getWinnerTest()
{
        State current;
        PLAYER winner;

        initState(&current);
        current.field[1][1] = PLAYER1;
        current.field[0][0] = PLAYER1;
        current.field[2][2] = PLAYER1;
        getWinner(current, &winner);
        assert(winner == PLAYER1);

        initState(&current);
        current.field[1][1] = PLAYER1;
        current.field[0][2] = PLAYER1;
        current.field[2][0] = PLAYER1;
        getWinner(current, &winner);
        assert(winner == PLAYER1);

        initState(&current);
        current.field[0][0] = PLAYER1;
        current.field[0][1] = PLAYER1;
        current.field[0][2] = PLAYER1;
        getWinner(current, &winner);
        assert(winner == PLAYER1);

        initState(&current);
        current.field[0][0] = PLAYER1;
        current.field[1][0] = PLAYER1;
        current.field[2][0] = PLAYER1;
        getWinner(current, &winner);
        assert(winner == PLAYER1); 
        
        initState(&current);
        current.field[1][1] = PLAYER2;
        current.field[0][0] = PLAYER2;
        current.field[2][2] = PLAYER2;
        getWinner(current, &winner);
        assert(winner == PLAYER2);

        initState(&current);
        current.field[1][1] = PLAYER2;
        current.field[0][2] = PLAYER2;
        current.field[2][0] = PLAYER2;
        getWinner(current, &winner);
        assert(winner == PLAYER2);

        initState(&current);
        current.field[0][0] = PLAYER2;
        current.field[0][1] = PLAYER2;
        current.field[0][2] = PLAYER2;
        getWinner(current, &winner);
        assert(winner == PLAYER2);

        initState(&current);
        current.field[0][0] = PLAYER2;
        current.field[1][0] = PLAYER2;
        current.field[2][0] = PLAYER2;
        getWinner(current, &winner);
        assert(winner == PLAYER2);
}

void getBestChainTest()
{
        State current;
        PLAYER winner;

        initState(&current);
        current.field[0][0] = PLAYER2;
        current.field[0][1] = PLAYER1;
        current.field[1][2] = NOPLAYER;
        current.field[1][0] = PLAYER2;
        current.field[1][1] = PLAYER2;
        current.field[1][2] = PLAYER1;
        current.field[2][0] = PLAYER1;
        current.field[2][1] = PLAYER1;
        current.current_player = PLAYER2;
        StateChain stc;
        initStateChain(&stc);
        StateChain res;
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.chain[1].field[2][2] == PLAYER2);

        initState(&current);
        current.field[1][1] = PLAYER1;
        current.current_player = PLAYER2;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);

        initState(&current);
        current.field[0][0] = PLAYER1;
        current.field[2][2] = PLAYER2;
        current.current_player = PLAYER1;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);

        initState(&current);
        current.field[0][0] = PLAYER2;
        current.field[0][1] = PLAYER1;
        current.field[1][0] = PLAYER1;
        current.field[1][1] = PLAYER1;
        current.field[1][2] = PLAYER2;
        current.field[2][1] = PLAYER2;
        current.field[2][2] = PLAYER1;
        current.current_player = PLAYER2;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);

        initState(&current);
        current.field[2][0] = PLAYER1;
        current.current_player = PLAYER2;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);

        initState(&current);
        current.field[0][2] = PLAYER1;
        current.current_player = PLAYER2;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);
        


        initState(&current);
        current.field[2][2] = PLAYER1;
        current.current_player = PLAYER2;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);

        initState(&current);
        current.field[0][0] = PLAYER1;
        current.field[1][1] = PLAYER2;
        current.field[1][0] = PLAYER1;
        current.field[2][0] = PLAYER2;
        current.current_player = PLAYER1;
        initStateChain(&stc);
        initStateChain(&res);
        getBestChain(current, stc, &res);
        printStateChain(res);
        assert(res.val == 0);
}
