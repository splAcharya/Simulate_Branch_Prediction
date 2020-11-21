// C++ program for Merge Sort
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;


#define N 10
#define MAX_VALUE 50
#define MIN_VALUE 1

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

        if( i > nl-1){
            goto done_for_loop_left;
        }

        larr[i] = array[l + i];

        i++;

        goto for_loop_left;

    done_for_loop_left:

    j = 0;

    //copy to right temp array
    for_loop_right:

        if( j > nr-1){
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
        if((i > nl-1) || (j > nr-1)){
            goto done_merge_array_while_loop;
        }

        if(larr[i] <= rarr[j]){
            goto swap_upper;
        }

        if(larr[i] > rarr[j]){
            goto swap_lower;
        }

        swap_upper:
            array[k] = larr[i];
            i++;
            k++;
            goto merge_array_while_loop;

        

        swap_lower:
            array[k] = rarr[j];
            j++;
            k++;
            goto merge_array_while_loop;


    done_merge_array_while_loop:

    // Copy the remaining elements of
    // L[], if there are any
    copy_remaining_left_while_loop:

        if(i > nl-1){
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

        if (j > nr-1) {
            goto done_copy_remaining_right_while_loop;
        }

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

	if (l < r) {

		// Same as (l+r)/2, but avoids
		// overflow for large l and h
		//int m = (l + r - l) / 2;
        int m = l + (r-l)/2;

		// Sort first and second halves
		mergeSort(array, l, m);

		mergeSort(array, m + 1, r);

		merge(array, l, m, r);
	}
}



// Driver code
int main()
{
	int *arr = generate_random_array(N,MIN_VALUE,MAX_VALUE);
    int arr_size = N;

	printf("Given array is \n");
	display_array_contents(arr, arr_size);

	mergeSort(arr, 0, arr_size - 1);

	printf("Sorted array is \n");
	display_array_contents(arr, arr_size);
	return 0;
}

