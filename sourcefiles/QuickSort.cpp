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
#define MAX 10
#define MIN 1


/*
* This function returns a dynamic integer array, the contents of this array are random numbers between the 
* range specifed as max and min in parameters. The size of the array is specifed by the length parameter. 
*@param length the length of the array or the number of elements to be genrate in the array
*@param min the minimum value for the random number generation
*@param max the maximum value for the random bumber generation
*@returns a dynamic integer array
*/
int * generate_random_array(int length, int min, int max){

    //intialize random seed
    srand(time(NULL));

    
    int * intAr  = new int[length];

    //initialze count to zero
    int count = 0;

    //generate random number between
    gen_loop:
        if (count > length-1){

            return intAr;
        }

        *(intAr + count) = (rand()% (max-min)) + min;

        count = count + 1;

        goto gen_loop;
}


/*
*This function displays the contents of a dynamic array.
*@param *ar the dynamic integer array whose contents are to be displayed
*@param ar_size the number of elements inside the array or the lengh of the array
*@returns None
*/
void display_array_contents(int * ar, int ar_size){

    //initialize count
    int count = 0;

    display_loop:
        if (count > ar_size - 1){
            return;
        }

        printf("%d ", *(ar + count) );

        count = count + 1;

        goto display_loop;
}


/*
* This function
*/
int paritition(int *ar, int low_index, int high_index){

    //select the  pivot as the last element of the array
    int pivot = *(ar + high_index);

    //index of smaller element
    int i = low_index - 1;

    //intialize count for loop
    int j = low_index;

    //end index for the loop
    int end_index = high_index - 1;

    //start partition
    partition_loop:

        if( j > high_index -1){

           //swap numbers
           int temp = *(ar + i + 1);

           *(ar + i + 1) = *(ar + high_index);

           *(ar + high_index) = temp;

           return (i+1);
        }

        //if current element is smaller than the pivot
        if( *(ar + j)  < pivot ){

            i = i + 1; //increment index of smaller element

            //swap numbers
            int temp = *(ar+i);

            *(ar+i) = *(ar + j);

            *(ar+j) = temp;

        }

    
        j = j + 1;

        goto partition_loop;

    return 0;
}



void quickSort(int * ar, int low_index, int high_index){

    if(low_index < high_index){

        int partition_index = paritition(ar,low_index,high_index);

        quickSort(ar, low_index, partition_index - 1);

        quickSort(ar, partition_index + 1, high_index);
    }

}


int main(int argc, char *argv[]){
    
    printf("\n****Simulation of Dynamic Branch Prediction Scheme****\n");

    int * intAr = generate_random_array(N,MIN,MAX);

    printf("Array Before Sorting: \n");

    display_array_contents(intAr, N);

    printf("\n");

    quickSort(intAr,0,N-1);

    printf("Array After Sorting: \n");

    display_array_contents(intAr, N);

    printf("\n");

    delete intAr;

    return 0;
}