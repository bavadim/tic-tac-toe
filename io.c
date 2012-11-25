#include "io.h"
#include <stdio.h>

void printState(State st)
{
        printf("\nPlayer %+i turn!\n", st.current_player);
        int i,j;
        for (i = 0; i < 3; ++i)
        {
                for (j = 0; j < 3; ++j)
                {
                        char* cell_val = " ";
                        if (st.field[i][j] == PLAYER1)
                                cell_val = "X";
                        else if (st.field[i][j] == PLAYER2)
                                cell_val = "0";

                        printf("%s|", cell_val);
                }
                printf("\n");
        }
}

void printStates(State sts[], int len)
{
        int i;
        for (i = 0; i < len; ++i)
                printState(sts[i]);
}

void printStateChain(StateChain chain)
{
        printf("\nOptimal game. Stages count: %i, Points: %i\n", chain.len, chain.val);
        int i;
        for (i = 0; i < chain.len; ++i)
                printState(chain.chain[i]);
}

