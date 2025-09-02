#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main (int argc , char *argv[])

{
    int max=1000000 , k , i , j , c ;
    char txt[max] , ctxt[max] ;

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    k = atoi(argv[1]);

    printf("plaintext : ") ;
    fgets(txt , sizeof(txt) , stdin) ;

    for ( i = 0 ; txt[i] != '\0' ; i++ )
      {
        if ( isalpha(txt[i]) )
         {
           if ( isupper(txt[i]) )
            {
              c = ( txt[i] - 'A' + k ) % 26 + 'A' ;
              ctxt[i] = c ;
            }
           else if ( islower(txt[i]) )
            {
              c = ( txt[i] - 'a' + k ) % 26 + 'a' ;
              ctxt[i] = c ;
            }
         }
        else
         {
           ctxt[i] = txt[i] ;
         }
      }
    ctxt[i] = '\0' ;
    printf("ciphertext : ") ;
    for ( j = 0 ; ctxt[j] != '\0' ; j++ )
      {
        printf("%c" , ctxt[j]) ;
      }

}
