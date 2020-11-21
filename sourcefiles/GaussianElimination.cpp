/*
*Author: Swapnil Acharya
*Date: 11/20/2020
*File: GaussianElimination.cpp
*Description: solving a system of linear equations. We will deal with the matrix of coefficients. 
* Gaussian Elimination does not work on singular matrices (they lead to division by zero)
*/

#include <stdlib.h>
#include <stdio.h>

#define NUM_BRANCHES 11
#define N 3   // Number of unknowns
#define TAKEN 1
#define NOT_TAKEN 0




// function for elementary operation of swapping two rows 
void swap_row(double mat[N][N+1], int i, int j) {

    //printf("Swapped rows %d and %d\n", i, j); 
    int  k = 0;

    for_loop_swap_row:

        if(k > N){
            return;
        }

        double temp = mat[i][k]; 
        mat[i][k] = mat[j][k]; 
        mat[j][k] = temp;

        k++;

        goto for_loop_swap_row;
} 


// function to calculate the values of the unknowns 
void backSub(double mat[N][N+1]) 
{ 
    double x[N];  // An array to store solution 
  
    // Start calculating from last equation up to the 
    //   first

    int j = 0;
    int i = N -1;

    for_loop_outer:

        if (i < 0){
            goto done_outer_for_loop;
        }

        // start with the RHS of the equation 
        x[i] = mat[i][N]; 

        // Initialize j to i+1 since matrix is upper 
        // triangular
        j = i + 1;

        for_loop_inner:

            if(j > N-1){
                goto done_inner_for_loop;
            }

            // subtract all the lhs values 
            // except the coefficient of the variable 
            // whose value is being calculated
            x[i] -= mat[i][j]*x[j]; 

            j++;

            goto for_loop_inner;


        done_inner_for_loop:

        // divide the RHS by the coefficient of the 
        // unknown being calculated
        x[i] = x[i]/mat[i][i]; 

        i--;

        goto for_loop_outer;

    done_outer_for_loop:


    int k = 0;

    printf("The Solution for Given Set of Equations: \n");

    display_sol_loop:

        if (k >= N){
            return;
        }

        printf("%lf\n",x[k]);

        k++;

        goto display_sol_loop;
}


// function to reduce matrix to r.e.f. 
int forwardElim(double mat[N][N+1]) 
{ 
    int k = 0;
    int i = 0;
    int j = 0;
    int i_max = 0;
    int v_max = 0;
    double f;

    outermost_for_loop:

        if(k > N-1){ //branch 1
            goto done_outermost_for_loop;
        }

        // Initialize maximum value and index for pivot 
        i_max = k; 
        v_max = mat[i_max][k]; 


        // find greater amplitude for pivot if any
        i = k+1;

        for_loop_amp:

            if( i > N-1){ //branch 2
                goto done_for_loop_amp;
            }
            
            if (abs(mat[i][k]) > v_max){ 
                v_max = mat[i][k];
                i_max = i;
            } 
            
            i++;
            goto for_loop_amp;
  
        done_for_loop_amp:

        // if a prinicipal diagonal element  is zero, 
        // it denotes that matrix is singular, and 
        // will lead to a division-by-zero later
        if (!mat[k][i_max]){

            goto singular_matrix_err;
            
            return k; // Matrix is singular
        }
             

        // Swap the greatest value row with current row
        if (i_max != k) {
            swap_row(mat, k, i_max); 
        }


        i = k+1;

        outer_for_loop:

            if( i > N-1){
                goto done_outer_for_loop;
            }

            // factor f to set current row kth element to 0, 
            // and subsequently remaining kth column to 0
            f = mat[i][k]/mat[k][k];

            // subtract 5th multiple of corresponding kth row element
            j = k + 1;

            inner_for_loop:

                if(j > N){
                    goto done_inner_for_loop;
                }

                // subtract fth multiple of corresponding kth row element
                mat[i][j] -= mat[k][j]*f;

                j++;

                goto inner_for_loop;

            done_inner_for_loop:

            // filling lower triangular matrix with zeros
            mat[i][k] = 0;

            i++;

            goto outer_for_loop;

        done_outer_for_loop:

        k++;

        goto outermost_for_loop;


    done_outermost_for_loop:
        return -1;
} 




// function to get matrix content 
void gaussianElimination(double mat[N][N+1]) 
{ 
    // reduction into r.e.f.
    int singular_flag = forwardElim(mat); 
  
    // if matrix is singular
    if (singular_flag != -1) 
    { 
        printf("Singular Matrix.\n"); 
  
        // if the RHS of equation corresponding to 
        //   zero row  is 0, * system has infinitely 
        //   many solutions, else inconsistent

        if (mat[singular_flag][N]) 
            printf("Inconsistent System.\n"); 
        else
            printf("May have infinitely many "
                   "solutions.\n"); 
  
        return; 
    } 
  
    // get solution to system and print it using 
    // backward substitution
    backSub(mat); 
} 


 
int main() 
{ 

    double mat[N][N+1] = {{3.0, 2.0,-4.0, 3.0}, 
                          {2.0, 3.0, 3.0, 15.0}, 
                          {5.0, -3, 1.0, 14.0} 
                         };  

    gaussianElimination(mat); 

    return 0; 
}