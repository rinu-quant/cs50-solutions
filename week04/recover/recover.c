#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if ( argc != 2 )
     {
       printf("usage: ./recover image\n") ;
       return 1 ;
     }
    FILE* ptr = fopen(argv[1] , "r") ;
    if ( ptr == NULL)
     {
       printf("could not open file\n") ;
       return 1 ;
     }
    FILE* img = NULL ;
    char file[8] ;
    int count = 0 ;
    unsigned char buffer[512] ;
    while ( fread( buffer , 512 , 1 , ptr ) == 1 )
     {
       if ( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 )
        {
          if ( img != NULL )
           {
             fclose(img) ;
           }
          sprintf ( file , "%03i.jpg" , count ) ;
          img = fopen ( file , "w" ) ;
          count++ ;
        }
       if ( img != NULL )
        {
          fwrite ( buffer , 512 , 1 , img ) ;
        }
     }
    if ( img != NULL )
     {
       fclose(img) ;
     }
    fclose(ptr) ;
    return 0 ;
}
