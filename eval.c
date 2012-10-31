#include "eval.h"

#include <stdio.h>
#include <string.h>
#include <limits.h>

/***********************PRIVATE STUFF***********************************/
int getPlayerCoff(PLAYER player)
{
        return player;
}

int checkRows(State state)
{
        int i;

        for (i = 0; i < 3; ++i)
                if (state.field[i][0] == state.field[i][1] && state.field[i][0] == state.field[i][2]
                        && state.field[i][0] != NOPLAYER)
                        return i;
        return -1;
}

int checkColumns(State state)
{
        int i;

        for (i = 0; i < 3; ++i)
                if (state.field[0][i] == state.field[1][i] && state.field[0][i] == state.field[2][i]
                                && state.field[0][i] != NOPLAYER)
                        return i;
        return -1;
}

int checkDiagonal(State state)
{
        short int res = -1;
        if (state.field[0][0] == state.field[1][1] && state.field[0][0] == state.field[2][2]
                        && state.field[0][0] != NOPLAYER)
                return 0;
        if (state.field[0][2] == state.field[1][1] && state.field[0][2] == state.field[2][0]
                        && state.field[0][2] != NOPLAYER)
                return 1;
        return -1;
}

BOOL fieldFull(State state)
{
        int i, j;

        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if (state.field[i][j] == NOPLAYER)
                                return FALSE;
        return TRUE;
}

PLAYER switchPlayer(State *state)
{
        PLAYER res;
        if (state->current_player == PLAYER1)
                res = PLAYER2;
        else
                res = PLAYER1;
        state->current_player = res;
        return res;
}

/*********************PUBLIC STUFF******************************************/
PLAYER getWinner(State current)
{
        short result = checkRows(current); 
        if (result != -1)
                return current.field[result][0];
        result = checkColumns(current);
        if (result != -1)
                return current.field[0][result];
        result = checkDiagonal(current);
        if (result != -1)
                return current.field[1][1];
        if (fieldFull(current) == TRUE)
                return NOPLAYER;

        return ERRORPLAYER;
}

int getNext(State current, State *next)
{
        int i,j;
        int count = 0;
        PLAYER current_p = current.current_player;

        /*after copy to new state*/
        switchPlayer(&current);

        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if (current.field[i][j] == NOPLAYER)
                        {
                                /*append new state*/
                                memcpy(next + count, &current, sizeof(State));
                                /*fill cell*/
                                next[count].field[i][j] = current_p;
                                ++count;
                        }

        return count;
}

int getValueAndBestChain(State *state, State *chain, int *count)
{        
        int i;
        int best_index  = 0;
        int best_val    = (INT_MIN + 1) * getPlayerCoff(state->current_player);
        State chain_buff[9][100];
        int   chain_len[9];
        State next_states[9];

        PLAYER winner = getWinner(*state);
        /*recursiion base*/
        if (winner != ERRORPLAYER)
        {
                memcpy(chain + *count, state, sizeof(State));
                ++(*count);
                return 5 * getPlayerCoff(winner);
        }

        for (i = 0; i < getNext(*state, next_states); ++i)
        {
                chain_len[i] = 0;
                int val = getValueAndBestChain(next_states + i, chain_buff[i], &chain_len[i]);

                if (val * getPlayerCoff(state->current_player) > best_val)
                {
                        best_index      = i;
                        best_val        = val;
                } 
        }

        /*Add to result chain*/
        memcpy(chain + *count, chain_buff[best_index], sizeof(State) * chain_len[best_index]);
        *count += chain_len[best_index];
        memcpy(chain + *count, state, sizeof(State));
        ++(*count);

        return best_val;
}


