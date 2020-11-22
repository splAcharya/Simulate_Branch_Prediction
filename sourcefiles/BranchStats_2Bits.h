#ifndef _BRANCH_STATS_2_BITS_H_
#define _BRANCH_STATS_2_BITS_H_


#include <stdlib.h>
#include <stdio.h>

const int NOT_TAKEN = 0;
const int TAKEN = 1;

const int STATE_00 = 1000;
const int STATE_01 = 2000;
const int STATE_10 = 3000;
const int STATE_11 = 4000;

class BranchStats_2Bits{

    private:
        int number_of_taken_branches;

        int number_of_not_taken_branches;

        int branch_predictor_state;
        
        int number_of_correct_predictions;

        int number_of_miss_predictions;

    public:

        BranchStats_2Bits(){
            this->number_of_taken_branches = 0;

            this->number_of_not_taken_branches = 0;

            this->branch_predictor_state = STATE_00;

            this->number_of_correct_predictions = 0;

            this->number_of_miss_predictions = 0;
        }

        BranchStats_2Bits(int state){
            this->number_of_taken_branches = 0;

            this->number_of_not_taken_branches = 0;

            this->branch_predictor_state = state;

            this->number_of_correct_predictions = 0;

            this->number_of_miss_predictions = 0;
        }

        void increase_num_taken_branches(){
            this->number_of_taken_branches++;
        }

        int get_num_taken_branches() const{
            return this->number_of_taken_branches;
        }

        void increase_num_not_taken_branches(){
            this->number_of_not_taken_branches++;
        }

        int get_num_not_taken_branches() const{
            return this->number_of_not_taken_branches;
        }


        int get_num_correct_predictions() const{
            return this->number_of_correct_predictions;
        }

        int get_num_miss_predictions() const{
            return this->number_of_miss_predictions;
        }

        void print_statistics(){
            printf("Number of Taken Branches: %d\n",this->number_of_taken_branches);
            printf("Number of Not Taken Branches: %d\n",this->number_of_not_taken_branches);
            printf("Number of Correct Branch Predictions: %d\n",this->number_of_correct_predictions);
            printf("Number of Miss Branch Predictions: %d\n",this->number_of_miss_predictions);

            double total_predictions = this->number_of_correct_predictions + this->number_of_miss_predictions;
            double cpr = this->number_of_correct_predictions / total_predictions;
            double mpr = this->number_of_miss_predictions / total_predictions;
            printf("Correct Branch Prediction : %0.2f %%\n", cpr*100);
            printf("Miss Branch Prediction : %0.2f %% \n", mpr*100);
        }

        void update_predictions(int program_action){

            //update predictions if it was correct or not correct
            if(this->branch_predictor_state == STATE_11){

                //STATE 11 Predicts TAKEN
                if(program_action == TAKEN){ //if program action was taken
    
                    this->number_of_correct_predictions++;
                    //state stays the same
                }
                else{ //if program action was not taken
                    this->number_of_miss_predictions++;

                    //update to STATE_10
                    this->branch_predictor_state = STATE_10;
                }
            }
            else if(this->branch_predictor_state == STATE_10){

                //STATE 10 Predicts TAKEN
                if(program_action == TAKEN){ //if program action was taken
                    this->number_of_correct_predictions++;
                    this->branch_predictor_state = STATE_11;
                }
                else{ //if program action was not taken
                    this->number_of_miss_predictions++;

                    //update to STATE_00
                    this->branch_predictor_state = STATE_00;

                }
            }
            else if(this->branch_predictor_state == STATE_00){

                //STATE 00 Predicts NOT TAKEN

                if(program_action == TAKEN){ //if program action was taken
                    this->number_of_miss_predictions++;
                    this->branch_predictor_state = STATE_01;
                }
                else{ //if program action was not taken
                    this->number_of_correct_predictions++;

                    //STATE DOES NOT CHANGE
                }
                
            }
            else{ //STATE_01

                //STATE 01 Predicts NOT TAKEN

                if(program_action == TAKEN){ //if program action was taken

                    this->number_of_miss_predictions++;

                    this->branch_predictor_state = STATE_11;
                }
                else{ //if program action was not taken
                    this->number_of_correct_predictions++;

                    //update to STATE_00
                    this->branch_predictor_state = STATE_00;
                }
            }
        }
};




#endif