/*
*Author: Swapnil Acharya
*Date: 11/21/2020
*File: MergeSort.cpp
*/


// C++ program for Merge Sort
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//Problem size
const int N = 200;


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
            
            goto done_for_loop_left;
        }
        
        larr[i] = array[l + i];

        i++;

        goto for_loop_left;

    done_for_loop_left:

    j = 0;

    //copy to right temp array
    for_loop_right:

        if( j > nr-1){ //BRANCH 2

            goto done_for_loop_right;
        }

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

            goto done_merge_array_while_loop;
        }

        if(larr[i] <= rarr[j]){ //BRANCH 4, data dependent branching

            array[k] = larr[i];
            i++;
            k++;

            goto merge_array_while_loop;
        }

        if(larr[i] > rarr[j]){ //BRANCH 5, data dependent branching

            array[k] = rarr[j];
            j++;
            k++;

            goto merge_array_while_loop;
        }

    done_merge_array_while_loop:

    // Copy the remaining elements of
    // L[], if there are any
    copy_remaining_left_while_loop:

        if(i > nl-1){ //BRANCH 6

            goto done_copy_remaining_left_while_loop;
        }      
        
        array[k] = larr[i];
        i++;
        k++;

        goto copy_remaining_left_while_loop;


    done_copy_remaining_left_while_loop:

    // Copy the remaining elements of
    // R[], if there are any

    copy_remaining_right_while_loop:

        if (j > nr-1) { //BRANCH 7

            goto done_copy_remaining_right_while_loop;
        }

        array[k] = rarr[j];
        j++;
        k++;

        goto copy_remaining_right_while_loop;

    done_copy_remaining_right_while_loop:
        return;   
}


/*
* This function sort an input array based on merge sort Algorithm.
* Merge Sort is based on dive and conquer approach. Merge sort 
* partitions an input array into two halves, then recursively calls 
* itself for the two partitions, and then merge the two sort partitions. 
* @param array the input integer array that is to be sorted
* @param l the left or the lower index of the array or the section of the
*  array to be sorted
* @param r the right or the upper index of the array or the section of the
*  array to be sorted
* @returns None the input array is sorted when the function is complete
*/
void mergeSort(int *array, int l, int r)
{
    int m;


	if(l > r - 1){ //BRANCH 0
		
		goto done_merge_sort;
	}
	
	//get the middle index for array partition
	// Same as (l+r)/2, but avoids overflow for large l and h
	m = l + (r-l)/2;

	//Recursively call the firt half of the array for sorting
	mergeSort(array, l, m);

	//Recursively call the firt half of the array for sorting
	mergeSort(array, m + 1, r);

	//Merge the sorted halves
	merge(array, l, m, r);

	done_merge_sort:
		//just a dummy bariabel so that the label "done_merge_sort" works
		int done = 0; 
	
}		



// Driver code
int main()
{
    printf("***********Simulation of Base Algorithms for Predictors **************\n\n");

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


	return 0;
}
