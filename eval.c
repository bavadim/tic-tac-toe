#include "eval.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

void getBestChain(State current, StateChain chain, StateChain *res_chain)
{                
        StateChain chn;
        copyStateChain(chain, &chn);
        appandStateToChain(current, &chn);
        
        PLAYER winner;
        if (getWinner(current, &winner))
        {
                assert((winner == 0) || (winner == -1) || (winner == 1));
                chn.val = (winner == NOPLAYER ? 0 : getPlayerCoff(winner));
                copyStateChain(chn, res_chain);
                return;
        }

        State next[10];
        res_chain->val = NAN;
        
        int count = getNext(current, next);

        assert(count > 0);
        int i;
        for (i = 0; i < count; ++i)
        {
                StateChain tmp;
                getBestChain(next[i], chn, &tmp);

                //get best turns chain value for current player (max or min)
                if (tmp.val * getPlayerCoff(current.current_player) > res_chain->val * getPlayerCoff(current.current_player))
                        copyStateChain(tmp, res_chain);
        }
        assert(res_chain->len > 0);
        assert((res_chain->val == -1) || (res_chain->val == 0) || (res_chain->val == 1));
}

void appandStateToChain(State st, StateChain *chain)
{

        chain->chain[(chain->len)++] = st;
}

BOOL getWinner(State current, PLAYER *result)
{
        short res = checkRows(current); 
        if (res != NOPLAYER)
        {
                *result = res;
                return TRUE;
        }
        res = checkColumns(current);
        if (res != NOPLAYER)
        {
                *result = res;
                return TRUE;
        }
        res = checkDiagonal(current);
        if (res != NOPLAYER)
        {
                *result = res;
                return TRUE;
        }
        if (fieldFull(current) == TRUE)
        {
                *result = NOPLAYER;
                return TRUE;
        }
        return FALSE;
}

int getNext(State current, State *next)
{
        PLAYER old_player = current.current_player;
        current.current_player = switchPlayer(current);

        int i,j;
        int count = 0;
        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if ((current.field[i][j] != PLAYER1) && (current.field[i][j] != PLAYER2))
                        {
                                copyState(current, (next + count));
                                next[count].field[i][j] = old_player;
                                ++count;
                        }

        return count;
}

void initState(State *st)
{
        st->current_player = PLAYER1;
        int i,j;
        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        st->field[i][j] = NOPLAYER;
}

void initStateChain(StateChain *chain)
{
        chain->len = 0; 
        //TODO!
        chain->val = 0;
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
        if ((st1.current_player != st2.current_player))
                return FALSE;
        int i,j;
        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if (st1.field[i][j] != st2.field[i][j])
                                return FALSE;
        return TRUE;
}

/***********************PRIVATE STUFF***********************************/
int getPlayerCoff(PLAYER player)
{
        return player;
}

PLAYER checkRows(State state)
{
        int i;

        for (i = 0; i < 3; ++i)
                if (state.field[i][0] == state.field[i][1] && state.field[i][0] == state.field[i][2]
                        && state.field[i][0] != NOPLAYER)
                        return state.field[i][0];
        return NOPLAYER;
}

PLAYER checkColumns(State state)
{
        int i;
        for (i = 0; i < 3; ++i)
                if ((state.field[0][i] == state.field[1][i]) && (state.field[0][i] == state.field[2][i])
                                && (state.field[0][i] != NOPLAYER))
                        return state.field[0][i];
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
        int i, j;

        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if (state.field[i][j] == NOPLAYER)
                                return FALSE;
        return TRUE;
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


