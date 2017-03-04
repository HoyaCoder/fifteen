//*
// Author James Meehan
// CS50 PSET3 Game of Fifteen
//*


/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int d);
void draw(void);
bool move(int tile);
bool won(int b);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    
    // greet user with instructions
    greet();

    // initialize the board
    init(d);
   

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int d)
{
    int size = d * d;
    if ((size - 1) % 2 == 0)
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                board[i][j] = size - 1;
                size --;
            }
        }
    }
    else 
    {
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                board[i][j] = size - 1;
                size --;
            }
            
        }
    int temp = board [d - 1][d - 2];
    board [d - 1][d - 2] = board [d - 1][d - 3];
    board [d - 1][d - 3] = temp;
      
    }
   
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    
    for (int l = 0; l < d; l++)
        {
            for (int k = 0; k < d; k++)
            {
                if (board [l][k] == 0 )
                {
                    printf("_  ");
                }
                else
                {
                printf("%2d  ", board[l] [k]);
                }
            }
            printf("\n");
        }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tile_row;
    int tile_column;
    int zero_row;
    int zero_column;
    
    
    for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (board[i][j] == 0) 
                {
                    zero_row = i;
                    zero_column = j;
                }
            }
        }
        
        
     for (int k = 0; k < d; k++)
        {
            for (int l = 0; l < d; l++)
            {
                if (board[k][l] == tile) 
                {
                    tile_row = k;
                    tile_column = l;
                }
            }
        }
   
   if (tile_row != zero_row && tile_column != zero_column)
   {
       return false;
   }
   else if (tile_row == zero_row && (tile_column == zero_column + 1 || tile_column == zero_column - 1))
   {
       int temp2 = board[zero_row][zero_column];
       board[zero_row][zero_column] = board[tile_row][tile_column];
       board[tile_row][tile_column] = temp2;
       return true;
   }
   else if (tile_column == zero_column && (tile_row == zero_row + 1 || tile_row == zero_row - 1))
   {
        int temp2 = board[zero_row][zero_column];
       board[zero_row][zero_column] = board[tile_row][tile_column];
       board[tile_row][tile_column] = temp2;
       return true;
   }
   else
   {
       return false;
   }
   
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int b)
{
    int size = b * b;
    
    for (int p = 0; p < b; p++)
    {
        for (int q = 0; q < b; q++)
        {
            if(board[p][q] != size + 1 - b * b)
            {
                if (p == b - 1 && q == b - 1 && board[p][q] == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else 
            {
                size++;
            }
        }
    }
    
    return false;
}
