#include "helpers.h"

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
    int fr,fg,fb;
    int count;
    RGBTRIPLE tmp[height][width];
    for(int i = 0 ; i < height ; i++)
    {

        for(int j = 0 ; j < width ; j++)
        {
           averr = 0;
           averg = 0;
           averb = 0;
           count = 0;



           if(j > 0 && i > 0) // upper left
           {
               count += 1;
               averr += image[i-1][j-1].rgbtRed;
               averg += image[i-1][j-1].rgbtGreen;
               averb += image[i-1][j-1].rgbtBlue;
           }

           if(i > 0) // upper
           {
                count += 1;
                averr += image[i-1][j].rgbtRed;
                averg += image[i-1][j].rgbtGreen;
                averb += image[i-1][j].rgbtBlue;
           }


           if( (j < width -1) && (i > 0)) //upper right
           {
               count += 1;
               averr += image[i-1][j+1].rgbtRed;
               averg += image[i-1][j+1].rgbtGreen;
               averb += image[i-1][j+1].rgbtBlue;
           }


           if(j > 0) // left
           {
               count += 1;
               averr += image[i][j-1].rgbtRed;
               averg += image[i][j-1].rgbtGreen;
               averb += image[i][j-1].rgbtBlue;
           }

           //current
           averr += image[i][j].rgbtRed;
           averg += image[i][j].rgbtGreen;
           averb += image[i][j].rgbtBlue;
           count += 1;


           if(j < width - 1) // right
           {
               count += 1;
               averr += image[i][j+1].rgbtRed;
               averg += image[i][j+1].rgbtGreen;
               averb += image[i][j+1].rgbtBlue;
           }


           if(j > 0 && i < height - 1) // down left
           {
               count += 1;
               averr += image[i+1][j-1].rgbtRed;
               averg += image[i+1][j-1].rgbtGreen;
               averb += image[i+1][j-1].rgbtBlue;
           }

           if (i < height -1) //down
           {
               count += 1;
               averr += image[i+1][j].rgbtRed;
               averg += image[i+1][j].rgbtGreen;
               averb += image[i+1][j].rgbtBlue;
           }

           if(j < width -1 && i < height -1) //down right
           {
               count += 1;
               averr += image[i+1][j+1].rgbtRed;
               averg += image[i+1][j+1].rgbtGreen;
               averb += image[i+1][j+1].rgbtBlue;
           }



            fr = round(averr / (float) count);
            fg = round(averg / (float) count);
            fb = round(averb / (float) count);

            if(fr > 255)
            {
                fr = 255;
            }

            if (fg > 255)
            {
                fg = 255;
            }

            if(fb > 255)
            {
                fb = 255;
            }


            tmp[i][j].rgbtRed = fr;
            tmp[i][j].rgbtGreen = fg;
            tmp[i][j].rgbtBlue = fb;

        }
    }

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
