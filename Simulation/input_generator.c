#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define NO_OF_PTS 1000
#define NO_OF_THS 16

#define RAND() 0 + rand()%(10000)

int main()
{
    srand(time(NULL));
    
    FILE* fp;
    fp = fopen("input.txt","w");

    if(fp == NULL)
    {
        printf("ERROR!! File opening is not successful.");
        return EXIT_FAILURE;
    }
    
    int src_x,src_y;
    src_x = RAND();
    src_y = RAND();
    
    fprintf(fp, "%d\n(%d,%d)\n%d\n", NO_OF_THS, src_x, src_y, NO_OF_PTS);
    
    for(int i = 0; i < NO_OF_PTS; i++)
    {
        int dest_x, dest_y;
        dest_x = RAND();
        dest_y = RAND();

        if(i == NO_OF_PTS - 1)
            fprintf(fp, "(%d,%d)", dest_x, dest_y);
        else
            fprintf(fp, "(%d,%d) ", dest_x, dest_y);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}