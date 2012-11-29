#include "eval.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

void searchBestSubchein(int current_player_cof, State avalible_states[10], int count, StateChain *result)
{
        int i;
        result->val = NAN;
        StateChain current_chain;
        copyStateChain(*result, &current_chain);
        for (i = 0; i < count; ++i)
        {
                StateChain tmp;
                copyStateChain(current_chain, &tmp);
                getBestChain(avalible_states[i], &tmp);

                //get best turns chain value for current player (max or min)
                if (tmp.val * current_player_cof > result->val * current_player_cof)
                        copyStateChain(tmp, result);
        }
        assert(result->len >= 0 && result->len <= 10);
        assert((result->val == -1) || (result->val == 0) || (result->val == 1));
}

void getBestChain(State current, StateChain *res_chain)
{                
        assert(res_chain->len >= 0 && res_chain->len <= 10);
        appandStateToChain(current, res_chain);
        
        PLAYER winner;
        if (getWinner(current, &winner))
        {
                assert((winner == NOPLAYER) || (winner == PLAYER1) || (winner == PLAYER2));
                res_chain->val = (winner == NOPLAYER ? 0 : getPlayerCoff(winner));
                return;
        }

        State next[10];
        int count = getNext(current, next);
        assert(count > 0);
        searchBestSubchein(getPlayerCoff(current.current_player), next, count, res_chain);
}

BOOL getWinner(State current, PLAYER *result)
{
        int res = (checkRows(current) ^ checkColumns(current) ^ checkDiagonal(current));
        assert((res == PLAYER1) || (res == PLAYER2) || (res == NOPLAYER));
        
        if ((res == PLAYER1) || (res == PLAYER2))
        {
                *result = res;
                return TRUE;
        }
        if (fieldFull(current))
        {
                *result = NOPLAYER;
                return TRUE;
        }
        *result = ERRORPLAYER;
        return FALSE;
}

int getNext(State current, State *next)
{
        PLAYER old_player = current.current_player;
        current.current_player = switchPlayer(current);

        int row, cel;
        int count = 0;
        for (row = 0; row < 3; ++row)
                for (cel = 0; cel < 3; ++cel)
                        if ((current.field[row][cel] != PLAYER1) && (current.field[row][cel] != PLAYER2))
                        {
                                copyState(current, (next + count));
                                next[count].field[row][cel] = old_player;
                                ++count;
                        }

        return count;
}

State getStateChainTop(const StateChain *chain)
{
        assert (chain->len > 0);
        return chain->chain[1];
}

void initState(State *st)
{
        memset(st, NOPLAYER, sizeof(State));
        st->current_player = PLAYER1;
}

void initStateChain(StateChain *chain)
{
        memset(chain, 0, sizeof(StateChain));
}

void appandStateToChain(State st, StateChain *chain)
{
        chain->chain[(chain->len)++] = st;
}

void copyStateChain(StateChain src, StateChain *dest)
{
        memcpy(dest, &src, sizeof(StateChain));
}

void copyState(State src, State *dest)
{
        memcpy(dest, &src, sizeof(State));
}

BOOL compareStates(State st1, State st2)
{
        return (memcmp(&st1, &st2, sizeof(State)) == 0);
}

void swapState(State *st1, State *st2)
{
        State tmp;
        copyState(*st1, &tmp);
        copyState(*st2, st1);
        copyState(tmp, st2);
}

PLAYER switchPlayer(State state)
{
        PLAYER res;
        if (state.current_player == PLAYER1)
                return PLAYER2;
        else if (state.current_player == PLAYER2)
                return PLAYER1;
        else if (state.current_player == NOPLAYER)
                return NOPLAYER;
        assert(FALSE);
        return ERRORPLAYER;
}
/***********************PRIVATE STUFF***********************************/
int getPlayerCoff(PLAYER player)
{
        return player;
}

PLAYER checkRows(State state)
{
        int row;
        for (row = 0; row < 3; ++row)
                if (state.field[row][0] == state.field[row][1] && state.field[row][0] == state.field[row][2]
                        && state.field[row][0] != NOPLAYER)
                        return state.field[row][0];
        return NOPLAYER;
}

PLAYER checkColumns(State state)
{
        int col;
        for (col = 0; col < 3; ++col)
                if ((state.field[0][col] == state.field[1][col]) && (state.field[0][col] == state.field[2][col])
                                && (state.field[0][col] != NOPLAYER))
                        return state.field[0][col];
        return NOPLAYER;
}

PLAYER checkDiagonal(State state)
{
        if ((state.field[0][0] == state.field[1][1] && state.field[0][0] == state.field[2][2]
                        && state.field[0][0] != NOPLAYER)
                || (state.field[0][2] == state.field[1][1] && state.field[0][2] == state.field[2][0]
                        && state.field[0][2] != NOPLAYER))
                return state.field[1][1];
        return NOPLAYER;
}

BOOL fieldFull(State state)
{
        int row, col;
        for (row = 0; row < 3; ++row)
                for (col = 0; col < 3; ++col)
                        if (state.field[row][col] == NOPLAYER)
                                return FALSE;
        return TRUE;
}

