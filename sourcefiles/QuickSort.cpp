/*
*Author: Swapnil Acharya
*Date: 11/20/2020
*File: QuickSort.cpp
*Description: Implement an algorithm to simulate the 
use of dynamic branch prediction schemes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define MAX 500
#define MIN 100


int * generate_random_array(){

    //intialize random seed
    srand(time(NULL));

    //generate random number between
    int * intAr  = new int[N];


    int count = 0;

    // goto gen_loop;

    gen_loop:
        if (count > N-1){

            printf("Count: %d\n",count);

            return intAr;
        }

        *(intAr + count) = (rand()% (MAX-MIN)) + MIN;

        count = count + 1;

        goto gen_loop;
}


int main(int argc, char *argv[]){
    
    printf("****Simulation of Dynamic Branch Prediction Scheme****\n");


    int * intAr = generate_random_array();

    for(int i=0; i < 20; i++){

        printf(" Val(%d): %d\n",i,*(intAr + i));
    }

    return 0;
}