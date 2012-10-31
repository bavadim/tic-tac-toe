#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER  int
#define PLAYER1 1
#define PLAYER2 -1 
#define NOPLAYER 0
#define ERRORPLAYER   999
#define BOOL    int
#define TRUE    1
#define FALSE   0

typedef struct State_struct
{
        PLAYER  field[3][3];
        PLAYER  current_player;
} State;

BOOL getTurn(State current, State *avalible)
{
        int i = 0, j = 0, val = 0, maxval = 0;
        State   next_states[9];
        int state_val[9];

        int count = getNext(current, next_states);

        if (!count)
                return FALSE;

        state_val[0] = -999;
        for (i = 0; i < count; ++i)
        {
                val = getValue(next_states[i], current.current_player);
                if (val > maxval)
                {
                        j = i;
                        maxval = val;
                }
        }

        memcpy(avalible, next_states + j, sizeof(State));
        
        return TRUE;
}

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
        int i,j = 0;
        int count = 0;
        PLAYER current_p = current.current_player;

        //after copy to new state
        switchPlayer(&current);

        for (i = 0; i < 3; ++i)
                for (j = 0; j < 3; ++j)
                        if (current.field[i][j] == NOPLAYER)
                        {
                                memcpy(next + count, &current, sizeof(State));
                                next[count].field[i][j] = current_p;
                                ++count;
                        }

        return count;
}

int getValue(State state, PLAYER pl)
{        
        int i;
        int best_index  = 0;
        int best_val    = -999;
        int len = 0;
        int val = 0;
        int coff = 0;

        State next_states[9];
        len = getNext(state, next_states);
        //recursiion base
        if (len == 0)
        {
                return 5 * getPlayerCoff(getWinner(state)) * getPlayerCoff(pl);
        }

        for (i = 0; i < len; ++i)
        {
                //pinalize for each level in tree
                val = getValue(next_states[i], pl) - 1; 
                if (val > best_val)
                {
                        best_index      = i;
                        best_val        = val; 
                }
        }

        return best_val;
}

///
int getPlayerCoff(PLAYER player)
{
        return player;
}

int checkRows(State state)
{
        int i = 0;

        for (i = 0; i < 3; ++i)
                if (state.field[i][0] == state.field[i][1] && state.field[i][0] == state.field[i][2]
                        && state.field[i][0] != NOPLAYER)
                        return i;
        return -1;
}

int checkColumns(State state)
{
        int i = 0;

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
        if (state.field[2][0] == state.field[1][1] && state.field[0][0] == state.field[0][2]
                        && state.field[2][0] != NOPLAYER)
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
//
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
        int i = 0;

        printf("\nPlayer %+i turn!\n", st.current_player);
        for (i = 0; i < 3; ++i)
                printf("%+i|%+i|%+i\n", st.field[i][0], st.field[i][1], st.field[i][2]);
}

int max_array(int a[], int num_elements)
{
   int i, max=-32000;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i]>max)
	 {
	    max=a[i];
	 }
   }
   return(max);
}
//
void main()
{
        int i,j = 0;
        int count = 0;
        State st;
        State avalible_turns[9];

        initializeState(&st);

        count = getTurn(st, avalible_turns);

        if (!count)
                return;

        printState(avalible_turns[0]);
}

