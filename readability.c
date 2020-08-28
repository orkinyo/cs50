#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
int not_letters(char*,int);
int count_words(char*,int);
int count_sent(char*,int);
float aver(int, int);
void r(int);

int main(void)
{
    string s = get_string("Text: ");
    int len = strlen(s);
    int fake = not_letters(s,len); //not letters
    int letters = len - fake; //actual letters
    int num_words = count_words(s,len);
    int sent = count_sent(s,len);
    double L = aver(letters, num_words);
    double S = aver(sent,num_words);
    double score = 0.0588 * L - 0.296 * S - 15.8;
    //printf("%d letter(s)\n%d word(s)\n%d sentence(s)\n",letters,num_words,sent);
    r((int) round(score));

}

int not_letters(char* s,int len)
{
    int num = 0;
    for(int i =0 ; i<len ; i++)
    {
        if (!((s[i] >= 'A' && s[i] <= 'Z' ) || (s[i] >= 'a' && s[i] <= 'z')))
        {
            num++;
        }
    }
    return num;
}

int count_words(char* s, int len)
{
    int count = 0;
    bool in = 0;

    for(int i = 0 ; i < len ; i++)
    {
        if(s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
        {
            in = 0;
        }
        else if(!in)
        {
            in = 1;
            count++;
        }
    }
    return count;
}

int count_sent(char* s, int len)
{
    int c = 0;
    bool in = 0;
    for(int i = 0 ; i < len ; i ++)
    {
        if(s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            in = 0;
        }
        else if(!in)
        {
            in = 1;
            c++;
        }
    }

    return c;
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