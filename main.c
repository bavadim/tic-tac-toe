#include "eval.h"
#include <stdio.h>

void initializeState(State *st)
{
        int i,j = 0;

        st->current_player = PLAYER1;
        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        st->field[i][j] = 0;
}

void printState(State st)
{
        int i, j;
        char *r1;

        printf("\nPlayer %+i turn!\n", st.current_player);
        for (i = 0; i < 3; ++i)
        {
                for (j = 0; j < 3; ++j)
                {
                        r1 = " ";
                        if (st.field[i][j] == PLAYER1)
                                r1 = "X";
                        else if (st.field[i][j] == PLAYER2)
                                r1 = "0";

                        printf("%s|", r1);
                }
                printf("\n");
        }
}

void main()
{
        int i = 0,j = 0;
        int count = 0;
        State st;
        State next[100];

        initializeState(&st);

        count = getValueAndBestChain(&st, next, &i);

        for (j = 0; j < i; ++j)
                printState(next[j]);
}

