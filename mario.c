#include <cs50.h>
#include <stdio.h>

int check(int);

int main(void)
{
    int num, spaces;
    int res = 0;
    while(!res)
    {
        num = get_int("Height:\t");
        res = check(num);
    }

    printf("\n");

    spaces = num - 1;
    for (int i = 1 ; i <= num ; i ++)
    {
        for(int j = 0 ; j < spaces ; j++)
        {
            printf(" ");
        }
        for(int j = 1 ; j <= i ; j++)
        {
            printf("#");
        }
        printf(" ");
        for(int j = 1 ; j <= i ; j++)
        {
            printf("#");
        }
        printf("\n");
        spaces--;

    }
}

int check(int num)
{
    if (num < 1)
    {
        return 0;
    }

    if (num > 8)
    {
        return 0;
    }

    return 1;
}