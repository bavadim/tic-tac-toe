#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "io.h"

void strupper(const char* in, char *out, int outlen)
{
        strncpy(out, in, outlen);
        char *c = out;
        while ((*c = toupper(*c)) != '\0')
                ++c;
}

void doTurn(State in, State *out, int row, int cel)
{
       copyState(in, out);
       out->field[row][cel] = in.current_player;
       out->current_player = switchPlayer(in);
}

BOOL isCellAvalible(State st, int row, int col)
{
        if ((row >= 0) && (row < 3) 
                        && (col >= 0) && (col < 3) 
                        && (st.field[row][col] == NOPLAYER))
                return TRUE;
        return FALSE;
}

char* getPlayerSign(PLAYER p)
{
        if (p == PLAYER1)
                return "X";
        if (p == PLAYER2)
                return "0";
        return " ";
}

void printState(State st)
{
        int row, cel;
        printf("    C1 C2 C3\n\n");
        for (row = 0; row < 3; ++row)
        {
                printf("R%i  |", row + 1);
                for (cel = 0; cel < 3; ++cel)
                        printf("%s|", getPlayerSign(st.field[row][cel]));
                printf("\n");
        }
        printf("\n");
        
        PLAYER winner;
        if (!getWinner(st, &winner))
        {
                printf("Player %s turn!\n", getPlayerSign(st.current_player));
                return;
        }
        if (winner == NOPLAYER)
                printf("Dead heat!\n");
        else if (winner != ERRORPLAYER)
                printf("Player %s wins!\n", getPlayerSign(winner));
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

BOOL askTurn(State in, State *out)
{
        printf("Your turn (RowNum ColumnNum, or <Ctrl + C> for Quit): ");
        
        char input[128];
        int row, col;
        while (TRUE)
        {
                int res = scanf("%i %i", &row, &col); 
                if (res == EOF)
                {
                        printf("error %i occure\n", errno);
                        return FALSE;
                }
                if (res != 2)
                {
                        printf("Invalid input. Please try again: ");
                        scanf("%*[^\n]"); //clean stdin
                        continue;
                }
                --row; --col;
                if (!isCellAvalible(in, row, col))
                {
                        printf("Cell R%i C%i is occupied or invalid. Please try again: ", row + 1, col + 1);
                        continue;
                }
                doTurn(in, out, row, col);
                return TRUE; 
        }

        return FALSE;
}  
