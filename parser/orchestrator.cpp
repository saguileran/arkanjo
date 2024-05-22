#include <bits/stdc++.h> 

#include "path.hpp"
#include "function.hpp"
#include "utils.hpp"
#include "similarity_table.hpp"
#include "similar_function_finder.hpp"
#include "counter_duplication_code_trie.hpp"
#include "counter_duplication_code.hpp"
#include "similarity_explorer.hpp"
#include "big_clone_formater.hpp"
#include "big_clone_tailor_evaluator.hpp"
using namespace std;


//HERE will be a temporary code to enable me to show up the functionalities I implemented to other people.
class Orchestrator{
	private:

		void help_command(){
			cout << "Sorry I am tired I will do this latter" << '\n';
		}

		void check_update_similarity(vector<string> parameters, Similarity_Table *similarity_table){
			int number_parameters = parameters.size();
			for(int i = 0; i < number_parameters-1; i++){
				string param = parameters[i];
				string next_param = parameters[i+1];
				if(param == "-s"){
					similarity_table->update_similarity(stod(next_param));
				}
			}
		}

		void exploration_command(vector<string> parameters, Similarity_Table *similarity_table){
			int number_parameters = parameters.size();

			string pattern = "";
			int limiter = 0;
			bool both_need_to_match = false;
			bool sorted_by_number_of_duplicated_code = false;
			for(int i = 0; i < number_parameters-1; i++){
				string param = parameters[i];
				string next_param = parameters[i+1];
				if(param == "-l"){
					limiter = stoi(next_param);
				}
				if(param == "-p"){
					pattern = next_param;
				}
				if(param == "-b"){
					both_need_to_match = (next_param == "T");
				}
				if(param == "-c"){
					sorted_by_number_of_duplicated_code = (next_param == "T");
				}
			}
			Similarity_Explorer similarity_explorer(
					similarity_table,
					limiter,
					pattern,
					both_need_to_match,
					sorted_by_number_of_duplicated_code);
		}

		void duplication_command(vector<string> parameters, Similarity_Table *similarity_table){
			Counter_Duplication_Code counter_duplication_code(similarity_table);
		}

		void big_clone_formater_command(vector<string> parameters, Similarity_Table *similarity_table){
			Big_Clone_Formater big_clone_formater(similarity_table);
		}

		void big_clone_tailor_evaluator_command(vector<string> parameters, Similarity_Table *similarity_table){
			Big_Clone_Tailor_Evaluator big_clone_tailor_evaluator(similarity_table);
		}

		void similar_function_finder_command(vector<string> parameters, Similarity_Table *similarity_table){
			int number_parameters = parameters.size();
			if(number_parameters == 0){
				cout << "ERROR: Similar Function Finder Command expect one parameter, but none was given" << endl;
				exit(0);
			}
			Similar_Function_Finder similar_function_finder(parameters[0],similarity_table);
		}

	public:
		Orchestrator(string command, vector<string> parameters){
			Similarity_Table similarity_table;
			check_update_similarity(parameters,&similarity_table);

			if(command == "du"){
				duplication_command(parameters,&similarity_table);
			}else if(command == "ex"){
				exploration_command(parameters,&similarity_table);
			}else if(command == "fu"){
				similar_function_finder_command(parameters,&similarity_table);
			}else if(command == "bi"){
				big_clone_formater_command(parameters,&similarity_table);
			}else if(command == "ev"){
				big_clone_tailor_evaluator_command(parameters,&similarity_table);
			}else{
				help_command();
			}
		}
};

int main(int argc, char *argv[]){
	string command = "";
	vector<string> parameters;
	if(argc >= 2){
		command = string(argv[1]);
	}
	for(int i = 2; i < argc; i++){
		string param(argv[i]);
		parameters.push_back(param);
	}

	Orchestrator(command,parameters);

	return 0;
}

