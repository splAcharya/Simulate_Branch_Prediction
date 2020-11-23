/*
*Author: Swapnil Acharya
*Date: 11/21/2020
*File: MergeSort_3Bit.cpp
*/


// C++ program for Merge Sort
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "BranchStats_3Bits.h"

using namespace std;

//Problem size
const int N = 200;

//Branch Prediction Parameters
const int TOTAL_BRANCHES = 8;


//declare a global stats 
BranchStats_3Bits branch_stats[TOTAL_BRANCHES];


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

            printf("\n");

            return;
        }

        printf("%d ", *(ar + count) );

        count = count + 1;

        goto display_loop;

    
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int *array, int l, int m, int r)
{
    int i , j , k, nl, nr;

   //size of left sub-arrays
   nl = m-l+1; 
   
   //size of right sub-arrays
   nr = r-m;
   
   // Create temp arrays
   int larr[nl];
   
   int rarr[nr];

    //copy to left temp array
    i = 0;

    for_loop_left:

        if( i > nl-1){ //BRANCH 1
            
            //update taken branch stats
            branch_stats[1].increase_num_taken_branches();
            branch_stats[1].update_predictions(TAKEN);

            goto done_for_loop_left;
        }

        //update not taken branch stats
        branch_stats[1].increase_num_not_taken_branches();
        branch_stats[1].update_predictions(NOT_TAKEN);
        

        larr[i] = array[l + i];

        i++;

        goto for_loop_left;

    done_for_loop_left:

    j = 0;

    //copy to right temp array
    for_loop_right:

        if( j > nr-1){ //BRANCH 2

            //update taken branch stats
            branch_stats[2].increase_num_taken_branches();
            branch_stats[2].update_predictions(TAKEN);

            goto done_for_loop_right;
        }

        //update not taken branch stats
        branch_stats[2].increase_num_not_taken_branches();
        branch_stats[2].update_predictions(NOT_TAKEN);


        rarr[j] = array[m + 1 + j];
        
        j++;

        goto for_loop_right;

    done_for_loop_right:

    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    i = 0;
 
    // Initial index of second subarray
    j = 0;   

    // Initial index of merged subarray
    k = l;



    //merge arrays
    merge_array_while_loop:
        
        //converting while to if, took 2 hours but nedded to change logic from && to ||
        if((i > nl-1) || (j > nr-1)){ //BRANCH 3

            //update taken branch stats
            branch_stats[3].increase_num_taken_branches();
            branch_stats[3].update_predictions(TAKEN);

            goto done_merge_array_while_loop;
        }
        
        //update not taken branch stats
        branch_stats[3].increase_num_not_taken_branches();
        branch_stats[3].update_predictions(NOT_TAKEN);

        if(larr[i] <= rarr[j]){ //BRANCH 4, data dependent branching

            array[k] = larr[i];
            i++;
            k++;

            //update taken branch stats
            branch_stats[4].increase_num_taken_branches();
            branch_stats[4].update_predictions(TAKEN);

            goto merge_array_while_loop;
        }

        //update not taken branch stats
        branch_stats[4].increase_num_not_taken_branches();
        branch_stats[4].update_predictions(NOT_TAKEN);

        if(larr[i] > rarr[j]){ //BRANCH 5, data dependent branching

            array[k] = rarr[j];
            j++;
            k++;

            //update taken branch stats
            branch_stats[5].increase_num_taken_branches();
            branch_stats[5].update_predictions(TAKEN);

            goto merge_array_while_loop;
        }

        //update not taken branch stats
        branch_stats[5].increase_num_not_taken_branches();
        branch_stats[5].update_predictions(NOT_TAKEN);

    done_merge_array_while_loop:

    // Copy the remaining elements of
    // L[], if there are any
    copy_remaining_left_while_loop:

        if(i > nl-1){ //BRANCH 6

            //update taken branch stats
            branch_stats[6].increase_num_taken_branches();
            branch_stats[6].update_predictions(TAKEN);

            goto done_copy_remaining_left_while_loop;
        }

        //update not taken branch stats
        branch_stats[6].increase_num_not_taken_branches();
        branch_stats[6].update_predictions(NOT_TAKEN);        
        
        array[k] = larr[i];
        i++;
        k++;

        goto copy_remaining_left_while_loop;


    done_copy_remaining_left_while_loop:

    // Copy the remaining elements of
    // R[], if there are any

    copy_remaining_right_while_loop:

        if (j > nr-1) { //BRANCH 7

            //update taken branch stats
            branch_stats[7].increase_num_taken_branches();
            branch_stats[7].update_predictions(TAKEN);

            goto done_copy_remaining_right_while_loop;
        }

        //update not taken branch stats
        branch_stats[7].increase_num_not_taken_branches();
        branch_stats[7].update_predictions(NOT_TAKEN);

        array[k] = rarr[j];
        j++;
        k++;

        goto copy_remaining_right_while_loop;

    done_copy_remaining_right_while_loop:
        return;   
}


// l is for left index and r is
// right index of the sub-array
// of arr to be sorted 
void mergeSort(int *array, int l, int r)
{
    int m;

	if(l > r - 1){ //BRANCH 0
		
		//update taken branch stats
        branch_stats[0].increase_num_taken_branches();
        branch_stats[0].update_predictions(TAKEN);
		
		goto done_merge_sort;
	}
	
	//update not taken branch stats
    branch_stats[0].increase_num_not_taken_branches();
    branch_stats[0].update_predictions(NOT_TAKEN);
	
	// Same as (l+r)/2, but avoids
	// overflow for large l and h
	//int m = (l + r - l) / 2;
	m = l + (r-l)/2;

	// Sort first and second halves
	mergeSort(array, l, m);

	mergeSort(array, m + 1, r);

	merge(array, l, m, r);

	done_merge_sort:
		int done = 0;
	
}		



// Driver code
int main()
{
    printf("***********Simulation of 3 Bit Branch Prediction Scheme**************\n\n");

    printf("***********Algorithm Used: Merge Sort*******************************\n\n");

    printf("**********Reading Numbers From File*********************************\n\n");
	FILE *fp;
    fp = fopen("rand_numbers.txt","r");
    int *arr = new int[N];
    for(int i = 0; i < N ; i++){
        fscanf(fp,"%d",(arr+i));
    }


	printf("***************Generated Array of Random Numbers ******************\n");
	display_array_contents(arr, N);
    printf("\n");

    printf("**************Started Sorting*************************************\n\n");
    mergeSort(arr, 0, N - 1);

	printf("**************Sorted Array is*************\n\n");
	display_array_contents(arr, N);
    printf("\n");

    printf("*********Branch Statistics***********\n\n");
    for(int i = 0; i < TOTAL_BRANCHES; i++){
        printf("Branch: %d\n",i);
        branch_stats[i].print_statistics();
        printf("\n");
    }


	return 0;
}
