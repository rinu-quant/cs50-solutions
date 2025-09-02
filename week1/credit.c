#include<stdio.h>
#include<cs50.h>

int main (void)

{
    long crdn , num , fst2 ;
    int pos=0 , x=0 , sum , sum1=0 , sum2=0 , dig , tmp , fst1 ;
    crdn = get_long ("Enter the card number : ");
    num = crdn;
    fst2 = crdn;

    while ( num > 0 ; )
     {
       dig = num%10;
       if ( pos % 2 == 0 )
        {
          sum1 = sum1 + dig ;
        }
       else
        {

          tmp = dig * 2 ;

          if ( tmp > 9 )
           {
             tmp = (tmp%10)+(tmp/10);
           }

          sum2 = sum2 + tmp ;

        }

       num = num/10;
       pos++;
       x++;

     }

    sum = sum1 + sum2 ;

    if ( sum % 10 == 0 )
     {
       while ( fst2 > 100 )
        {
          fst2 = fst2/10;
        }
       fst1 = fst2/10;
       if ( x == 15 )
        {
          if ( fst2 == 34 || fst2 == 37 )
           {
             printf("AMEX\n");
           }
        }
       else if ( x == 16 )
        {
          switch (fst2)
           {
             case 51:
             case 52:
             case 53:
             case 54:
             case 55:
              printf("MASTERCARD\n");
              break;
             default :
              if ( fst1 == 4 )
               {
                 printf("VISA\n");
               }
              else
               {
                 printf("INVALID\n");
               }
            }
         }
        else if ( x == 13 && fst1 == 4 )
         {
           printf("VISA\n");
         }
         else
          {
           printf("INVALID\n");
          }
     }
    else
     {
       printf("INVALID\n");
     }


}


































































