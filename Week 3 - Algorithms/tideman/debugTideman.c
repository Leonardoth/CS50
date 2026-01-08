#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int willLoop(int winner, int loser);

int main(int argc, string argv[])
{
    // // Check for invalid usage
    // if (strcmp(argv[1],"debug") != 0)
    // {
    //     printf("Usage: tideman debug\n");
    //     return 1;
    // }

    // // Populate array of candidates
    // candidate_count = 3;
    // if (candidate_count > MAX)
    // {
    //     printf("Maximum number of candidates is %i\n", MAX);
    //     return 2;
    // }

    // candidates[0] = "Alice";
    // candidates[1] = "Bob";
    // candidates[2] = "Charlie";

    // // Clear graph of locked in pairs
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         locked[i][j] = false;
    //     }
    // }

    // pair_count = 0;
    // int voter_count = 9;

    // add_pairs();
    // sort_pairs();


   int setup_pairs[] = {2, 3,
                     6, 1,
                     3, 6,
                     1, 2,  // skipped
                     1, 3,  // skipped
                     3, 5,
                     5, 0,
                     0, 2,  // skipped
                     2, 6,
                     4, 6,
                     4, 2,
                    };

    pair_count = sizeof setup_pairs / sizeof setup_pairs[0] / 2;
    candidate_count = MAX;
    for (int i = 0, *setup = setup_pairs; i < pair_count; i++) {
    pairs[i].winner = *(setup++);
    pairs[i].loser = *(setup++);
    }

    lock_pairs();

    for (int i = 0; i < pair_count; i++)
    printf("%d->%d  %s\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser] ? "LOCKED!" : "--skip--");

    // return 0;
    // lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // Loop for each rank
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int candidate = ranks[i];
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[candidate][ranks[j]] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair newPair;
                newPair.winner = i;
                newPair.loser = j;
                pairs[pair_count] = newPair;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i+1; j < pair_count; j++)
        {
            int winner_i = pairs[i].winner;
            int loser_i = pairs[i].loser;
            int winner_j = pairs[j].winner;
            int loser_j = pairs[j].loser;
            int diff_i = preferences[winner_i][loser_i];
            int diff_j = preferences[winner_j][loser_j];
            if(diff_j > diff_i)
            {
                pair temp_i = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp_i;
            }

        }
    }
    return;
}



// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if (winner == loser)
        {
            break;
        }
        if (!willLoop(winner, loser))
        {
            printf("locking %i -> %i\n", winner, loser);
            locked[winner][loser] = 1;
        }

    }
    return;
}

int willLoop(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if(willLoop(winner, i))
            {
                return true;
            }
        }
    }

    return false;

}


// Print the winner of the election
void print_winner(void)
{
    // TODO
    int possibleWinners[MAX];
    for (int i = 0; i < candidate_count; i++){
        possibleWinners[i] = 1;
        int losses = 0;
        for (int j = 0; j < candidate_count; j++){
            if(locked[i][j]){
                possibleWinners[i]++;
            }
            if(locked[j][i]){
                printf("%i loses to %i\n", i, j);
                losses++;
            }
        }
        if (losses > 0){
            possibleWinners[i] = 0;
        }
    }

    int votes = -1;
    int winner = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if(possibleWinners[i] > votes){
            votes = possibleWinners[i];
            winner = i;
        }
    }

    printf("%i \n", winner);
    return;
}
