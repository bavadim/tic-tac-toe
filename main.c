#include "eval.h"
#include "io.h"

#include "tests.h"

void main()
{
        runTests();

        State st;
        initState(&st);

        StateChain res;
        initStateChain(&res);
        getBestChain(st, &res);
        printStateChain(res);
}

