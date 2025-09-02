#include<stdio.h>
#include<ctype.h>

int main (void)

{
    int point[26] = { 1 , 3 , 3 , 2 , 1 , 4 , 2 , 4 , 1 , 8 , 5 , 1 , 3 , 1 , 1 , 3 , 10 , 1 , 1 , 1 , 1 , 4 , 4 , 8 , 4 , 10 } ;
    char p1[100] , p2[100] ;
    int i , j , x , y , sum1 = 0 , sum2 = 0 ;

    printf("player 1 : ");
    scanf("%s", p1) ;
    printf("player 2 : ");
    scanf("%s", p2) ;

    for ( i = 0 ; p1[i] != '\0' ; i++ )
     {
       p1[i] = toupper(p1[i]) ;
       if ( isalpha(p1[i]))
        {
          x = p1[i] - 'A' ;
          sum1 = sum1 + point[x] ;
        }
     }

    for ( j = 0 ; p2[j] != 0 ; j++ )
     {
       p2[j] = toupper(p2[j]) ;
       if (isalpha(p2[j]))
        {
          y = p2[j] - 'A' ;
          sum2 = sum2 + point[y] ;
        }
     }


    if ( sum1 > sum2 )
     {
       printf("player 1 wins \n") ;
     }
    else if ( sum2 > sum1 )
     {
       printf("player 2 wins \n") ;
     }
    else
     {
       printf("Tie \n") ;
     }

}









