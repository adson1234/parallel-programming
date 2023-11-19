#include <iostream>
#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <pthread.h>

#define lld long long int
using namespace std;


int NUMTHREADS = 4;


lld number_in_circle = 0;
pthread_mutex_t gLock;

const int squar_region=RAND_MAX/2;  //32767/2=16383
const int squar_region2=squar_region*squar_region;

void *Func(void *pArg) {
    int x,y,distance_squared;
    lld number_of_tosses_athread=*((lld*)pArg);
    lld toss,my_number_in_circle=0;
    for ( toss = 0; toss < number_of_tosses_athread ; toss ++) {
        while((x = rand())==RAND_MAX);  //使隨機範圍為奇數
        x-=squar_region;
        while((y = rand())==RAND_MAX);  //使隨機範圍為奇數
        y-=squar_region;
        distance_squared = x * x + y * y ;
        if (distance_squared <= squar_region2)
            my_number_in_circle ++;
    }

    pthread_mutex_lock(&gLock);
    number_in_circle += my_number_in_circle;
    pthread_mutex_unlock(&gLock);
    return 0;
}

int main()
{
    /* 設定亂數種子 */
    srand( time(NULL) );
    //printf("RAND_MAX = %d\n", RAND_MAX);

    lld number_of_tosses;
    scanf("%d", &NUMTHREADS);
    scanf("%lld", &number_of_tosses);
    lld number_of_tosses_athread=number_of_tosses/NUMTHREADS;


    pthread_t thrds[NUMTHREADS];
    pthread_mutex_init(&gLock, NULL);
    for (int i = 0; i < NUMTHREADS; ++i ) {
        int rc=pthread_create(&thrds[i], NULL,Func,(void*)&number_of_tosses_athread);
        if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }
    for (int i = 0; i < NUMTHREADS; ++i )
        pthread_join(thrds[i], NULL);
    pthread_mutex_destroy(&gLock);


    double pi_estimate = 4* number_in_circle /(( double ) number_of_tosses );   // + 0.00031447758
    //cout << pi_estimate<<endl;
    printf("%.11f\n",pi_estimate);
    return 0;
}
