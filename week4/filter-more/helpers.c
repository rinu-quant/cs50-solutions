#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0 ; i < height ; i++ )
      {
        for ( int j = 0 ; j < width ; j++ )
          {
            RGBTRIPLE pixel = image[i][j] ;
            float sum = pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue ;
            float avg = sum/3 ;
            int grey = (int)round(avg) ;
            image[i][j].rgbtRed = grey ;
            image[i][j].rgbtBlue = grey ;
            image[i][j].rgbtGreen = grey ;
          }
      }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for ( int i = 0 ; i < height ; i++ )
      {
        for ( int j = 0 ; j < width/2 ; j++ )
          {
              RGBTRIPLE tmp = image[i][j] ;
              image[i][j] = image[i][width-1-j] ;
              image[i][width-1-j] = tmp ;
          }
      }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumr ;
    int sumb ;
    int sumg ;
    float count ;
    float avgr ;
    float avgb ;
    float avgg ;
    RGBTRIPLE tmp[height][width] ;
    for ( int i = 0 ; i < height ; i++ )
      {
        for ( int j = 0 ; j < width ; j++ )
          {
            sumr = 0 ;
            sumb = 0 ;
            sumg = 0 ;
            count = 0 ;
            for ( int k = i-1 ; k <= i+1 ; k++ )
             {
                for ( int l = j-1 ; l <= j+1 ; l++ )
                  {
                    if ( k == -1 || k == height || l == -1 || l == width )
                     {
                      continue ;
                     }
                    else
                     {
                       sumr += image[k][l].rgbtRed ;
                       sumg += image[k][l].rgbtGreen ;
                       sumb += image[k][l].rgbtBlue ;
                       count++ ;
                     }
                  }
             }
            avgr = sumr/count ;
            avgb = sumb/count ;
            avgg = sumg/count ;
            tmp[i][j].rgbtRed = (int)round(avgr) ;
            tmp[i][j].rgbtBlue = (int)round(avgb) ;
            tmp[i][j].rgbtGreen = (int)round(avgg) ;
          }
      }
    for ( int m = 0 ; m < height ; m++ )
      {
        for ( int n = 0 ; n < width ; n++ )
          {
            image[m][n] = tmp[m][n] ;
          }
      }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
   RGBTRIPLE tmp[height][width] ;
   int Gx[3][3] = { { -1 , 0 , 1 } , { -2 , 0 , 2 } ,  { -1 , 0 , 1 } } ;
   int Gy[3][3] = { { -1 , -2 , -1 } , { 0 , 0 , 0 } , { 1 , 2 , 1 } } ;
   int ti ;
   int tj ;
   int sumr ;
   int sumb ;
   int sumg ;

   for ( int i = 0 ; i < height ; i++ )
     {
       for ( int j = 0 ; j < width ; j++ )
         {
           int r1 = 0 ;
           int b1 = 0 ;
           int g1 = 0 ;
           int r2 = 0 ;
           int g2 = 0 ;
           int b2 = 0 ;
           for ( int k = -1 ; k <= 1 ; k++ )
             {
               for ( int l = -1 ; l <= 1 ; l++ )
                 {
                   ti = i + k ;
                   tj = j + l ;
                   if ( ti == -1  || ti == height || tj == -1 || tj == width )
                    {
                      continue ;
                    }
                   r1 = r1 + ( Gx[k+1][l+1] * image[ti][tj].rgbtRed ) ;
                   g1 = g1 + ( Gx[k+1][l+1] * image[ti][tj].rgbtGreen ) ;
                   b1 = b1 + ( Gx[k+1][l+1] * image[ti][tj].rgbtBlue ) ;

                   r2 = r2 + ( Gy[k+1][l+1] * image[ti][tj].rgbtRed ) ;
                   g2 = g2 + ( Gy[k+1][l+1] * image[ti][tj].rgbtGreen ) ;
                   b2 = b2 + ( Gy[k+1][l+1] * image[ti][tj].rgbtBlue ) ;
                 }
            }

           sumr = (int) round( sqrt(r1*r1 + r2*r2) ) ;
           if ( sumr > 255 )
            {
              sumr = 255 ;
            }
           sumg = (int) round( sqrt(g1*g1 + g2*g2) ) ;
           if ( sumg > 255 )
            {
              sumg = 255 ;
            }
           sumb = (int) round( sqrt(b1*b1 + b2*b2) ) ;
           if ( sumb > 255 )
            {
              sumb = 255 ;
            }

          tmp[i][j].rgbtRed = sumr ;
          tmp[i][j].rgbtBlue = sumb ;
          tmp[i][j].rgbtGreen = sumg ;

         }
      }
    for ( int m = 0 ; m < height ; m++ )
      {
        for ( int n = 0 ; n < width ; n++ )
          {
            image[m][n].rgbtRed = tmp[m][n].rgbtRed ;
            image[m][n].rgbtBlue = tmp[m][n].rgbtBlue ;
            image[m][n].rgbtGreen = tmp[m][n].rgbtGreen ;
          }
      }
    return;
}
