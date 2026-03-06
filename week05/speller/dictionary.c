// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 10000

node *table[N];
unsigned int count = 0 ;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word) ;
       node *n = table[index] ;
       while (n != NULL)
        {
          if ( strcasecmp ( word , n->word ) == 0 )
           {
             return true ;
           }
          n = n->next ;
        }
    return false ;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int sum = 0 ;
    for ( int i = 0 ; word[i] != 0 ; i++ )
      {
        sum = sum * 37 + tolower(word[i]) ;
      }
    return sum%N ;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen (dictionary,"r") ;
    if ( file == NULL )
     {
       printf ("Error in loading dictionary") ;
       return false ;
     }
    char word[LENGTH+1] ;
    while ( fscanf( file , "%s" , word ) != EOF )
     {
       node *list = malloc ( sizeof ( node ) ) ;
       if ( list == NULL )
        {
          fclose(file) ;
          return false ;
        }
       strcpy ( list->word , word ) ;
       list->next = NULL ;

       int index = hash ( word ) ;
       if ( table[index] == NULL )
        {
          table[index] = list ;
        }
       else
        {
          list->next = table[index] ;
          table[index] = list ;
        }
      count++ ;
     }
   fclose(file) ;
   return true ;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if ( count != 0)
     {
       return count ;
     }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *ptr ;
    for ( int i=0 ; i<N ; i++)
      {
        node *list = table[i] ;
        if (table[i] != NULL)
         {
           while ( list != NULL )
            {
              ptr = list->next ;
              free(list) ;
              list = ptr ;
            }
           table[i] = NULL ;
         }
      }
    return true ;
}

