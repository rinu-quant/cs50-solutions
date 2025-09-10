#include<stdio.h>
#include<cs50.h>

int main (void)

{
    int , height i , j , k , l ;

    do
    {
      height = get_int("Enter the block height? ");
    }
    while ( height < 1 || height > 8 );

    for ( i = 0 ; i < height ; i++ )
      {
        for ( j = height-1 ; j > 0 ; j-- )
          {
            for ( k = 0 ; k < height ; k++ )
              {
                 printf("#") ;
              }

            printf("  ");

            for ( l = 0 ; l < height ; l++ )
              {
                printf("#");
              }
            printf("\n");
         }
       }

}
