#include <stdio.h>
#include <string.h>

#include "io.h"

char* strsub(const char* str, int from, int count)
{
        if (strlen(str) < from + count)
                return NULL;
        return strndup(str + from, count);
}

void doTurn(State in, State *out, int row, int cel)
{
       copyState(in, out);
       out->field[row][cel] = in.current_player;
       out->current_player = switchPlayer(in);
}

BOOL parseTurn(const char *input, int* row, int* col)
{
        *row = -1; 
        *col = -1;

        char* input_row = strsub(input, 0, 2);
        char* input_col = strsub(input, 2, 2);

        char* avalible_actions = "R0R1R2C1C2C3";
        int i;
        for (i = 0; i < 6; i = i + 2)
        {
                if (strsub(avalible_actions, i, 2) == input_row)
                {
                        *row = i;
                        break;
                }
        }
        for (i = 6; i < 12; i = i + 2)
        {
                if (strsub(avalible_actions, i, 2) == input_col)
                {
                        *col = i;
                        break;
                }
        }
        if ((*row == -1) || (*col == -1))
                return FALSE;

        return TRUE;
}

BOOL isCellAvalible(State st, int row, int col)
{
        if (st.field[row][col] == NOPLAYER)
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
        printf("\nPlayer %s turn!\n", getPlayerSign(st.current_player));
        int row, cel;
        printf("    C1 C2 C3\n\n");
        for (row = 0; row < 3; ++row)
        {
                printf("R%i  |", row);
                for (cel = 0; cel < 3; ++cel)
                        printf("%s|", getPlayerSign(st.field[row][cel]));
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

BOOL askTurn(State in, State *out)
{
        printState(in);
        printf("\nYour turn (R<num>C<num> or q to quit): ");
        
        char input[128];
        while (fgets (input, 128, stdin) != NULL)
        {
                if (strstr("q", input) != NULL)
                        return FALSE;

                int row, col;
                if (!parseTurn(input, &row, &col) || !isCellAvalible(in, row, col))
                        return FALSE;
                
                doTurn(in, out, row, col);
                return TRUE; 
        }

        return FALSE;
}  
