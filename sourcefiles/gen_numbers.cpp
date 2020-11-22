/*
*Author: Swapnil Acharya
*Date: 11/22/2020
*File: gen_numbers.cpp
*Description: This program generates random numbers and writes them in a file 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* This function returns a dynamic integer array, the contents of this array are random numbers between the 
* range specifed as max and min in parameters. The size of the array is specifed by the length parameter. 
*@param length the length of the array or the number of elements to be genrate in the array
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

        int rand_num1 = (rand()% (25-1)) + 1;
        int rand_num2 = (rand()% (75-25)) + 25;
        int final_rand_num = rand_num1 + rand_num2;

        fprintf(fp,"%d ",final_rand_num);
    }

    fclose(fp);
}

