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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int j = 0; j < candidate_count - 1; j++)
    {
        for (int i = j + 1; i < candidate_count; i++)
        {
            preferences[ranks[j]][ranks[i]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int j = 0; j < candidate_count - 1; j++)
    {
        for (int i = j + 1; i < candidate_count; i++)
        {
            if (preferences[j][i] > preferences[i][j])
            {
                pair p;
                p.winner = j;
                p.loser = i;
                pairs[pair_count++] = p;
            }
            else if (preferences[j][i] < preferences[i][j])
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count++] = p;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        pair p1 = pairs[i];
        pair p2 = pairs[i + 1];

        if (preferences[p1.winner][p1.loser] < preferences[p2.winner][p2.loser])
        {
            pairs[i] = p2;
            pairs[i + 1] = p1;

            for (int j = i; j > 0; j--)
            {
                pair p4 = pairs[j];
                pair p3 = pairs[j - 1];

                if (preferences[p3.winner][p3.loser] < preferences[p4.winner][p4.loser])
                {
                    pairs[j] = p3;
                    pairs[j - 1] = p4;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair p = pairs[i];
        int as[MAX];
        int ascount = 0;
        as[ascount++] = p.loser;
        int count = 0;
        bool found = false;
        while (count < ascount)
        {
            for (int j = 0; j < pair_count; j++)
            {
                if (locked[as[count]][j])
                {
                    as[ascount++] = j;

                    if (j == p.winner)
                    {
                        found = true;
                        break;
                    }
                }
            }
            count++;
        }
        if (!found)
        {
            locked[p.winner][p.loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool found = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }

            if (locked[j][i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
