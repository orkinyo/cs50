#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
void r(int);
float aver(int,int);

int main(void)
{
    string s = get_string("Text: ");
    int lc = 0, wc = 0, sc = 0;
    int len = strlen(s);
    for(int i = 0 ; i < len ; i++)
    {
        if (isalpha(s[i]))
        {
            lc++;
        }
        else if(s[i] == ' ' )
        {
            wc++;
        }

        else if (i == len -1 )
        {
            if(isalpha(s[i-1]))
            {
                wc++;

            }
        }

        if((s[i-1] != '.' && s[i-1]!= '?' && s[i-1] != '"' && s[i-1] != '!' )&&(s[i] == '.' || s[i] == '?' || s[i] == '!' ))
        {

            sc++;
        }




    }

    double L = aver(lc, wc);
    double S = aver(sc,wc);
    double score = 0.0588 * L - 0.296 * S - 15.8;
    //printf("%d letter(s)\n%d word(s)\n%d sentence(s)\n",lc,wc,sc);
    r((int) round(score));

}

float aver(int letters, int words)
{
    float let = letters, w = words;
    return (float) let * (100.0/w);
}

void r(int d)
{
    if(d>=16)
    {
        printf("Grade 16+\n");
    }
    else if(d<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",d);
    }
}