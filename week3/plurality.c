#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name)
{
    for ( int j = 0 ; j < candidate_count ; j++ )
      {
        if ( strcmp(candidates[j].name,name) == 0 )
         {
            candidates[j].votes++;
            return true ;
         }
      }
    return false;
}

void print_winner(void)
{
    int total_vote = candidates[0].votes ;
    for ( int j = 0 ; j < candidate_count ; j++ )
      {
        if ( candidates[j].votes > total_vote )
         {
            total_vote = candidates[j].votes ;
         }
      }
      for ( int j = 0 ; j < candidate_count ; j++ )
        {
            if ( total_vote == candidates[j].votes )
             {
                printf("%s\n" , candidates[j].name) ;
             }
        }
    return;
}
