#include "eval.h"
#include "io.h"

void main()
{

        State st;
        initState(&st);

        StateChain chain;
        initStateChain(&chain);
        StateChain res;
        getBestChain(st, chain, &res);
        printStateChain(res);
}

