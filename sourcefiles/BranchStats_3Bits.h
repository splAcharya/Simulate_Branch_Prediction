#ifndef _BRANCH_STATS_3_BITS_H_
#define _BRANCH_STATS_3_BITS_H_


#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include <vector>

const int NOT_TAKEN = 0;
const int TAKEN = 1;



const int COMB_000 = 1000; //N,N,N
const int COMB_001 = 2000; //N,N,T
const int COMB_010 = 3000; //N,T,N
const int COMB_011 = 4000; //N,T,T
const int COMB_100 = 5000; //T,N,N
const int COMB_101 = 6000; //T,N,T
const int COMB_110 = 7000; //T,T,N
const int COMB_111 = 8000; //T,T,T




class BranchStats_3Bits{

    private:
        int number_of_taken_branches;

        int number_of_not_taken_branches;
        
        int number_of_correct_predictions;

        int number_of_miss_predictions;

        std::unordered_map<int,std::vector<int>> combination_table;

        std::vector<int> global_history_table;

        std::vector<int> initialize_with_vector(int action){

            std::vector<int> a_vector;

            a_vector.push_back(action);

            return a_vector;
        }


    public:

        BranchStats_3Bits(){

            this->number_of_taken_branches = 0;

            this->number_of_not_taken_branches = 0;

            this->number_of_correct_predictions = 0;

            this->number_of_miss_predictions = 0;

            //initialize combination tabel for 3 bit predictor
            for(int i=1000; i < 9000; i+= 1000){
                this->combination_table[i] = this->initialize_with_vector(NOT_TAKEN);
            }

            //initialize global history table with T,T,T
            this->global_history_table.push_back(COMB_111);

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
            printf("Correct Branch Prediction Rate: %0.2f %%\n", cpr*100);
            printf("Miss Branch Prediction Rate: %0.2f %% \n", mpr*100);
        }


        void update_predictions(int program_action){

            //get last item from history table
            int last_history = this->global_history_table.back();
            
            //get combination
            if(last_history == COMB_000){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_000].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_001);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_000);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_000].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_000);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_000].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_001);
                }

            }



            //get combination
            else if(last_history == COMB_001){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_001].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_001].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_001].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
        
            }



            //get combination
            else if(last_history == COMB_010){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_010].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_101);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_100);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_010].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_100);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_010].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_101);
                }
        
            }            



            //get combination
            else if(last_history == COMB_011){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_011].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_111);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_110);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_011].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_110);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_011].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_111);
                }
        
            } 



            //get combination
            else if(last_history == COMB_100){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_100].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_001);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_000);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_100].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_000);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_100].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_001);
                }
        
            } 



            //get combination
            else if(last_history == COMB_101){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_101].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_101].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_101].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
        
            } 



            //get combination
            else if(last_history == COMB_110){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_110].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_101);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_100);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_110].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_100);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_110].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_101);
                }
        
            }  



            //get combination
            else if(last_history == COMB_111){

                //go to combination table to get prediction
                int prediction = this->combination_table[COMB_111].back();

                //if prediction and program action were taken
                if((prediction == TAKEN) && (program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;
                    
                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
                //if prediction and program action were not taken
                else if( (prediction == NOT_TAKEN) && (program_action == NOT_TAKEN)){

                    //update number of correct predictions
                    this->number_of_correct_predictions++;

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( (prediction == TAKEN ) && (program_action == NOT_TAKEN) ){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_111].push_back(NOT_TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_010);
                }
                else if( ( prediction == NOT_TAKEN) && ( program_action == TAKEN)){

                    //update number of correct predictions
                    this->number_of_miss_predictions++;

                    //update combination_table
                    this->combination_table[COMB_111].push_back(TAKEN);

                    //update history table
                    this->global_history_table.push_back(COMB_011);
                }
        
            }                      
        }
};


#endif