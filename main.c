#include "eval.h"
#include "io.h"

void runGameCycle()
{
        State st1;
        State st2;
        initState(&st1);
        initState(&st2);

        do 
        {
                swapState(&st1, &st2);  
                StateChain res;
                initStateChain(&res);
                getBestChain(st1, &res);
                st1 = getStateChainTop(&res);
        } while (askTurn(st1, &st2));
}

void main()
{
        runGameCycle();
}
