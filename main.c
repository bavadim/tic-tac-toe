#include "eval.h"
#include "tests.h"
#include <stdio.h>

void main()
{
        nextTest();
        getWinnerTest();
        getBestChainTest();

        State st;
        initState(&st);

        StateChain chain;
        initStateChain(&chain);
        StateChain res;
        getBestChain(st, chain, &res);
        printStateChain(res);
}

