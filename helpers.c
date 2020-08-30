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
    int averr,averg,averb;
    int count;
    for(int i = 0 ; i < height ; i++)
    {
        count = 0;
        for(int j = 0 ; j < width ; j++)
        {
            if(j == width - 1)
            {
                if(i == height - 1)
                {
                    count = 4;
                    averr = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue;
                }
                else if (i == 0)
                {
                    count = 4;
                    averr = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue;
                }

                else
                {
                    count = 6;
                    averr = image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue;

                }
            }

            else if (j == 0)
            {
                if(i == height - 1)
                {
                    count = 4;
                    averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
                }

                else if (i == 0)
                {
                    count = 4;
                    averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
                }

                else
                {
                    count = 6;
                    averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed;
                    averg = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen;
                    averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue;
                }
            }

            else if(i == 0)
            {
                count = 6;
                averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed;
                averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue;
                averg = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen;
            }

            else if(i == height - 1)
            {
                count = 6;
                averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed;
                averg = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen;
                averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue;
            }

            else
            {
                count = 9;
                averr = image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j-1].rgbtRed;
                averg= image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen;
                averb = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue;


            }



            averr = (int) round((float) averr / (float) count);
            averb = (int) round((float) averg / (float) count);
            averg = (int) round((float) averb / (float) count);

            image[i][j].rgbtRed = averr;
            image[i][j].rgbtGreen = averg;
            image[i][j].rgbtBlue = averb;

        }
    }
    return;
}
