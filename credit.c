#include <stdio.h>
#include <cs50.h>

int digsum(long);

int main(void)
{

    long long number = get_long("Number: ");

    int sum1 = 0, sum2 = 0, total;
    int num_dig = 0;
    int i = 0;
    int comp = -1;

    int fin = 0;
    if (number < 1000000000000)
    {
        printf("INVALID\n");
        fin = 1;
    }


     while(number != 0)
     {
         if(number/100 == 0 && comp == -1)
         {

             if(number > 10)
             {
                 if (number == 34 || number == 37)
                 {
                     comp = 1; //Amex
                 }

                 else if(number == 51 || number == 52 || number == 53 || number == 54 || number == 55)
                 {
                     comp = 2; // MasterCard
                 }
             }

             if (number < 10)
             {
                 if (number == 4)
                 {

                     comp = 3; //visa
                 }

                 else
                 {
                     comp = 4 ; //Invalid
                 }
             }
         }
         if (i % 2 == 0)
         {
             sum1 += digsum(number % 10);

         }
         else
         {
             sum2 += digsum((number % 10 ) * 2);

         }
         i++;
         number = number / 10;
     }
     total = sum1 + sum2;
     if (total % 10 == 0 && !fin)
     {
         switch (comp)
         {
             case 1:
             printf("AMEX\n");
             break;

             case 2:
             printf("MASTERCARD\n");
             break;

             case 3:
             printf("VISA\n");
             break;

             case 4:
             printf("INVALID\n");
             break;
         }
     }

     else if (!fin)
     {
         printf("INVALID\n");
     }
    }

int digsum(long num)
{
    int sum = 0;
    num = (int) num;

    while(num>0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}