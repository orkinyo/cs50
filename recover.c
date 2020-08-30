#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#define block 512
#define name 8
typedef uint8_t BYTE;
int magic[] = {0xff, 0xd8, 0xff,14};
void inc(int* c1, int* c2, int* c3);
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage ./recover file\n");
        return 1;
    }
    char fname[name];   //store filename
    FILE* raw = fopen(argv[1],"r");

    if(raw == NULL)
    {
        printf("Cannot open\n");
        return 1;
    }

    BYTE buffer[block];
    bool flagfile = false;

    FILE* img = NULL;
    int counter = 0;


    printf("opened\n");


    while(fread(buffer,block,1,raw) == 1)
    {
        //printf("h\n");
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //is header of jpeg
        {
            //printf("here\n");

            if(flagfile)
            {
                fclose(img);
            }
            else
            {
                flagfile = true;
            }

            sprintf(fname,"%03d.jpg",counter);
            img = fopen(fname,"w");
            counter += 1;
            if(img == NULL)
            {
                printf("error opening out\n");
                return 1;
            }


        }

        if(flagfile)
        {
            fwrite(buffer,block,1,img); //write to img file
        }

    }

    fclose(img);
    fclose(raw);



}



