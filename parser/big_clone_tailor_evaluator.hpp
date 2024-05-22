#include <bits/stdc++.h> 

#include "path.hpp"
#include "utils.hpp"
#include "similarity_table.hpp"

using namespace std;

class Big_Clone_Tailor_Evaluator{
	string CLONE_LABELS_FILE_PATH = "/home/luan/linux/test-duplication-code/parser/bigclonebench/clone_labels.txt";
	string EXTENSION = ".java";
	int NUMBER_OF_TYPES = 6;
	int NOT_CLONE_TYPE_ID = 5;
	string RECALL_PER_TYPE_PRINT = "Recall Value of each type";
	double MINIMUM_SIMILARITY_TEMP = 90;
	vector<string> ID_TO_TYPE_LABEL = {
		"T1",
		"T2",
		"ST3",
		"MT3",
		"WT3/T4",
		"Negative",
	};

	Similarity_Table *similarity_table;
	map<pair<int,int>,int> id_pair_to_type;
	vector<int> count_of_samples_by_type;

	void read_clone_labels();
	int path_to_id(Path path);
	vector<tuple<double,int,int>> similar_path_pairs_formated_with_id();
	bool is_relevant_pair(int id0, int id1);

	vector<pair<int,int>> filter_similar_id_pairs_only_relevant_ones(
			vector<pair<int,int>> similar_id_pairs);

	vector<pair<int,int>> filter_similar_path_pairs_by_similarity(
			vector<tuple<double,int,int>> similar_id_pairs,
			double minimum_similarity);

	vector<int> build_frequency_corrected_guessed_by_type(
			vector<pair<int,int>> similar_id_pairs);

	double calc_recall(vector<int> frequency, int type);
	void print_recall_per_type(vector<int> frequency);

	void evaluate(double minimum_similarity);
	public:
	Big_Clone_Tailor_Evaluator(Similarity_Table *_similarity_table);
};
