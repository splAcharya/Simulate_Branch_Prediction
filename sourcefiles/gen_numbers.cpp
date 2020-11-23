/*
*Author: Swapnil Acharya
*Date: 11/22/2020
*File: gen_numbers.cpp
*Description: This program generates random numbers and writes them in a file.
*             The numbers of random numbers to be generated must be supplied as argument
*			  to the executable
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* This 
*@param min the minimum value for the random number generation
*@param max the maximum value for the random bumber generation
*@returns a dynamic integer array
*/
int main(int argc, char * argv[]){

    if(argc < 2){

        printf("Specify The numbers of random numbers to be generated \n");

        return 0;
    }

    int N = atoi(argv[1]);

    FILE *fp;

    fp = fopen("rand_numbers.txt","w+");

    //intialize random seed
    srand(time(NULL));

    //generate random number between
    for(int i = 0; i < N; i++){
        int final_rand_num = (rand()% (100-1)) + 1;
        fprintf(fp,"%d ",final_rand_num);
    }

    fclose(fp);
}

