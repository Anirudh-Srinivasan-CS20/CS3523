/************************************************************
            ASSIGNMENT 1 - OPERATING SYSTEM 2
                     Simulations
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define NO_OF_PTS 5000
#define NO_OF_THS 12

#define RAND() 0 + rand()%(10000)

struct point_t
{
    double x;
    double y;
};
typedef struct point_t point_t;

struct arg_t
{
    point_t src_pt;
    point_t* dest_pts;
    int pts_per_th;
};
typedef struct arg_t arg_t;

void print_point(point_t p)
{
    printf("(%lf,%lf)", p.x, p.y);
}

double euclidean_dist(point_t p1, point_t p2)
{
    return (sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)));
}

void* find_closest(void* args)
{    
        point_t* closest = ((arg_t*)args)->dest_pts;
        for(int i = 1; i < ((arg_t*)args)->pts_per_th; i++)
        {
            if(euclidean_dist(((arg_t*)args)->src_pt, ((arg_t*)args)->dest_pts[i]) < euclidean_dist(((arg_t*)args)->src_pt, *closest))
            {
                closest = ((arg_t*)args)->dest_pts + i; 
            }
        }

    return (void*) closest;    
}

void replace(char* str, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(str[i] =='(' || str[i] == ')' || str[i] == ',')
            str[i] = ' ';
    }
}


/*******************************************
 *            Main Function
*******************************************/

int main() 
{
    //srand(time(NULL));
    int no_of_th = NO_OF_THS; 
    int no_of_pt = NO_OF_PTS;
    
    point_t src_pt;
    src_pt.x = RAND();
    src_pt.y = RAND();

    
    point_t* points;
    points = (point_t*)malloc(no_of_pt * sizeof(point_t));

    if (points == NULL) 
    {
        printf("ERROR! Memory could not be allocated for all the points.\n");
        exit(EXIT_SUCCESS);
    }

    for(int i = 0; i < no_of_pt; i++)
    {
        points[i].x = RAND();
        points[i].y = RAND();
    }

    pthread_t worker_th[no_of_th];
     
    int pts_per_th = no_of_pt/no_of_th;
    
    point_t* res[no_of_th];
    arg_t args[no_of_th];

    clock_t starting_time, ending_time;

    starting_time = clock();
    
    for(int i = 0; i < no_of_th; i++)
    {
        args[i].src_pt = src_pt;
        args[i].dest_pts = points + i * pts_per_th;
        if(i == (no_of_th - 1) && (!(no_of_pt % no_of_th == 0)))
            args[i].pts_per_th = no_of_pt - (i * pts_per_th);
        else
            args[i].pts_per_th = pts_per_th;
        

        if((pthread_create(&worker_th[i], NULL, find_closest, (void*) &args[i]) != 0)) 
        {
            perror("ERROR! Failed to create thread.");
            return EXIT_FAILURE;
        }

    }  

    for(int i = 0; i < no_of_th; i++)
    {
        if((pthread_join(worker_th[i], (void**) &res[i]) != 0))
        {
            perror("ERROR! Failed to join thread.");
            return EXIT_FAILURE;
        }      

    }    

    point_t closest = *(res[0]);
    for(int i = 1; i < no_of_th; i++)
    {
        
        if(euclidean_dist(src_pt, *(res[i])) < euclidean_dist(src_pt,closest))
        {
            closest = *(res[i]);
        }
    }
    //sleep(1);
    ending_time = clock();

    clock_t time_reqd = ending_time - starting_time;
    printf("%lf microseconds \n",(double)(time_reqd * pow(10, 6)/CLOCKS_PER_SEC));
    print_point(closest);

    free(points);
    return EXIT_SUCCESS;
}