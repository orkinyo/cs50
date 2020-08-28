#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int get_idx(string,char);

string l = "abcdefghijklmnopqrstuvwxyz";
string u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc,char** argv)
{
    if(argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if(strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    int index;
    string p = get_string("plaintext:  ");
    char cipher[strlen(p)];
    //printf("%lu\n",strlen(p));
    printf("ciphertext: ");
    for(int i = 0 ; i < strlen(p) ; i++)
    {
        if(isupper(p[i]))
        {
            index = get_idx(u,p[i]);
            cipher[i] = toupper(argv[1][index]);
        }

        else if (islower(p[i]))
        {
            index = get_idx(l,p[i]);
            cipher[i] = tolower(argv[1][index]);
        }
        else
        {
            cipher[i] = p[i];
        }
        printf("%c",cipher[i]);
    }
    printf("\n");

}

int get_idx(string s, char c)
{
    for (int i = 0 ; i < strlen(s) ; i++ )
    {
        if (s[i] == c)
        {
            return i;
        }
    }
    return -1;
}
