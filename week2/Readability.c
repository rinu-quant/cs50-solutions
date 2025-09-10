#include<stdio.h>
#include<ctype.h>

int main (void)

{
    int max = 1000000;
    char txt[max];
    int i , j , w = -1 , index ;
    float l = 0 , s = 0  ;


    printf("Write your lines : \n");
    fgets(txt , sizeof(txt) , stdin );

    for ( i = 0 ; txt[i] != '\0' ; i++ )
      {
        if ( isalpha(txt[i]) )
         {
           l++;
         }
        else if ( isspace(txt[i]) )
         {
           w++;
         }
        else if ( txt[i] == '.' || txt[i] == '?' || txt[i] == '!' )
         {
           s++;
         }
      }


    s = (s/w)*100;
    l = (l/w)*100;
    index = (0.0588*l)-(0.296*s)-15.8 ;

    if ( index < 1 )
     {
       printf("Grade below 1 \n");
     }
    else if ( index > 16 )
     {
       printf("Grade 16+ \n");
     }
    else
     {
       printf("Grade %d\n" , index);
     }

}
