#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main ( int argc , char *argv[] )

{
    int max = 1000000 , i , j , k , l , m , n , y1 , y2 ;
    char alpha[52] , key[30] , txt[max] , vis[30] , x ;

    if ( argc != 2)
     {
       printf("Invalid key\n");
       return 1 ;
     }
    for ( l = 0 ; argv[1][l] != '\0' ; l++ )
      {
        if ( !isalpha(argv[1][l] ) )
         {
           printf("All character must me alphabets\n");
           return 1 ;
         }
       }

    strcpy(key , argv[1]) ;

    for ( i = 0 ; i < 26 ; i++)
      {
        alpha[i] = 'A' + i;
      }
    for ( i = 0 ; i < 26 ; i++ )
      {
        alpha[26+i] = 'a' + i ;
      }

    if ( strlen(key) == 26 )
     {
       for ( m = 0 ; key[m] != '\0' ; m++ )
         {
           x = toupper(key[m]) ;
           for ( n = m+1 ; key[n] != '\0' ; n++ )
             {
               if ( x == toupper(key[n]) )
                {
                  printf("All character must be unique\n") ;
                  return 0 ;
                }
             }
         }

       printf("plaintext: ") ;
       fgets( txt , sizeof(txt) , stdin ) ;
       txt[strcspn(txt,"\n")] = '\0' ;
       printf("ciphertext: ") ;

       for ( k = 0 ; txt[k] != '\0' ; k++ )
         {
           y1 = 0 ;
           y2 = 26 ;
           if ( isupper(txt[k]) )
            {
              while ( alpha[y1] != txt[k] && y1 < 26 )
                  {
                    y1++ ;
                  }
              printf("%c" , key[y1] ) ;
            }
           else if ( islower(txt[k]) )
            {
              while ( alpha[y2] != txt[k] && y2 < 52 )
                  {
                    y2++ ;
                  }
              printf("%c" , key[y2-26] ) ;
            }
           else
            {
              printf("%c" , txt[k] ) ;
            }
         }
     }
    else
     {
        printf("Key must contain 26 characters.") ;
     }

    printf("\n") ;

}
