#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float aver;
    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            aver = round(( (float) (image[i][j].rgbtRed) + (float) (image[i][j].rgbtGreen) + (float) (image[i][j].rgbtBlue) )/3.0);
            image[i][j].rgbtRed = (int) aver;
            image[i][j].rgbtGreen = (int) aver;
            image[i][j].rgbtBlue = (int) aver;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    float originalRed,originalBlue,originalGreen;
    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            originalRed = (float) image[i][j].rgbtRed;
            originalGreen = (float) image[i][j].rgbtGreen;
            originalBlue = (float) image[i][j].rgbtBlue;

            sepiaRed = (int) round(0.393 *  originalRed + 0.769 *  originalGreen + 0.189 *  originalBlue);
            sepiaGreen = (int) round(0.349 *  originalRed + 0.686 *  originalGreen + 0.168 *  originalBlue);
            sepiaBlue = (int) round(0.272 * originalRed + 0.534 *  originalGreen + 0.131 *  originalBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tr,tg,tb;
    for(int i = 0 ; i < height ; i++)
    {
        for(int j = 0 ; j < width/2 ; j++)
        {
            tr = image[i][j].rgbtRed;
            tb = image[i][j].rgbtBlue;
            tg = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width-j-1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width-j-1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-j-1].rgbtGreen;
            image[i][width-j-1].rgbtRed = tr;
            image[i][width-j-1].rgbtGreen = tg;
            image[i][width-j-1].rgbtBlue = tb;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int averr, averg, averb;
    int count;
    for(int i = 0 ; i < height ; i++)
    {

        for(int j = 0 ; j < width ; j++)
        {
           averr = 0; averg = 0; averb = 0; count = 0; //current
           averr += image[i][j].rgbtRed;
           averg += image[i][j].rgbtGreen;
           averb += image[i][j].rgbtBlue;
           count++;

           if(j < width -1 && i > 0) //upper right
           {
               count++;
               averr += image[i-1][j+1].rgbtRed;
               averg += image[i-1][j+1].rgbtGreen;
               averb += image[i-1][j+1].rgbtBlue;
           }

           if(j > 0 && i > 0) // upper left
           {
               count++;
               averr += image[i-1][j-1].rgbtRed;
               averg += image[i-1][j-1].rgbtGreen;
               averb += image[i-1][j-1].rgbtBlue;
           }

           if(j > 0) // left
           {
               count++;
               averr += image[i][j-1].rgbtRed;
               averg += image[i][j-1].rgbtGreen;
               averb += image[i][j-1].rgbtBlue;
           }

           if(i > 0) // upper
           {
               count++;
                averr += image[i-1][j].rgbtRed;
                averb += image[i-1][j].rgbtBlue;
                averg += image[i-1][j].rgbtGreen;
           }

           if(j < width - 1) // right
           {
               count++;
               averr += image[i][j+1].rgbtRed;
               averg += image[i][j+1].rgbtGreen;
               averb += image[i][j+1].rgbtBlue;
           }

           if(j < width -1 && i < height -1) //down right
           {
               count++;
               averr += image[i+1][j+1].rgbtRed;
               averg += image[i+1][j+1].rgbtGreen;
               averb += image[i+1][j+1].rgbtBlue;
           }

           if(j > 0 && i <height - 1) // down left
           {
               count++;
               averr += image[i+1][j-1].rgbtRed;
               averg += image[i+1][j-1].rgbtGreen;
               averb += image[i+1][j-1].rgbtBlue;
           }

           if (i > height -1) //down
           {
               count++;
               averr += image[i+1][j].rgbtRed;
               averg += image[i+1][j].rgbtGreen;
               averb += image[i+1][j].rgbtBlue;
           }





            averr = averr / count;
            averg = averg / count;
            averb = averb / count;

            image[i][j].rgbtRed = averr;
            image[i][j].rgbtGreen = averg;
            image[i][j].rgbtBlue = averb;

        }
    }
    return;
}
