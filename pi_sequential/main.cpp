#include <iostream>
#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

using namespace std;

#define lld long long int

int main()
{
    /* 設定亂數種子 */
    srand( time(NULL) );
    printf("RAND_MAX = %d\n", RAND_MAX);
    const int squar_region=RAND_MAX/2;  //32767/2=16383
    const int squar_region2=squar_region*squar_region;

    lld number_of_tosses, toss;
    cin >> number_of_tosses;
    lld number_in_circle = 0;

    int x,y,distance_squared;
    for ( toss = 0; toss < number_of_tosses ; toss ++) {
        while((x = rand())==RAND_MAX);
        x-=squar_region;
        while((y = rand())==RAND_MAX);
        y-=squar_region;
        distance_squared = x * x + y * y ;
        if (distance_squared <= squar_region2)
            number_in_circle ++;
    }
    double pi_estimate = 4* number_in_circle /(( double ) number_of_tosses ) ;
    cout << pi_estimate<<endl;
    return 0;
}
