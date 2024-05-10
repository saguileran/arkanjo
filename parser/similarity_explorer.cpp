/*
This file expect the output of parser.cpp
This code filter the output only printing the files similar to files that contains a given pattern passed as argc
The code filter every file that has the pattern as a substring, so be carefull with duplications
*/

#include <bits/stdc++.h> 

#include "similarity_explorer.hpp"

Utils::COLOR Similarity_Explorer::choose_text_color(){
	Utils::COLOR ret = Utils::GRAY;
	if(processed_results%2 == 0){
		ret = Utils::CYAN;
	}
	return ret;
}

int Similarity_Explorer::find_number_pairs_show(int number_pair_found){
	if(limit_on_results == UNLIMITED_RESULTS){
		return number_pair_found;
	}
	return min(limit_on_results,number_pair_found);
}

string Similarity_Explorer::format_initial_message(int number_pair_found){
	string ret;
	ret += INITIAL_TEXT_PRINT_1;
	ret += to_string(number_pair_found);
	ret += INITIAL_TEXT_PRINT_2;
	ret += to_string(find_number_pairs_show(number_pair_found));
	ret += INITIAL_TEXT_PRINT_3;
	return ret;
}

bool Similarity_Explorer::match_pattern(Path path1, Path path2){
	bool match1 = path1.contains_given_pattern(pattern_to_match);
	bool match2 = path2.contains_given_pattern(pattern_to_match);

	if(both_path_need_to_match_pattern){
		return match1 && match2;
	}
	return match1 || match2;
}

string Similarity_Explorer::format_path_message_in_pair(Path path){
	string ret = path.build_relative_path() + BETWEEN_RELATIVE_AND_FUNCTION_NAME + path.build_function_name();
	return ret;
}

int Similarity_Explorer::find_number_lines(Path path1){
	Function function(path1);
	return function.number_of_lines();
}

void Similarity_Explorer::print_similar_path_pair(Path path1, Path path2){
	string line;
	line += START_LINE_COMPARATION_PRINT;
	line += format_path_message_in_pair(path1);
	line += BETWEEN_TWO_FUNCTION;
	line += format_path_message_in_pair(path2);
	line += NUMBER_LINES_MESSAGE;
	line += to_string(find_number_lines(path1));

	Utils::COLOR color = choose_text_color();
	cout << Utils::format_colored_message(line,color) << '\n';
}

void Similarity_Explorer::process_similar_path_pair(Path path1, Path path2){
	if(!match_pattern(path1,path2)){
		return;
	}
	if(limit_on_results != UNLIMITED_RESULTS && processed_results >= limit_on_results){
		return;
	}
	processed_results++;
	print_similar_path_pair(path1,path2);
}

int Similarity_Explorer::find_number_pair_found(vector<pair<Path,Path>> similar_path_pairs){
	int count = 0;
	for(auto [path1, path2] : similar_path_pairs){
		if(match_pattern(path1,path2)){
			count++;
		}
	}
	return count;
}

void Similarity_Explorer::explorer(){
	vector<pair<Path,Path>> similar_path_pairs = similarity_table->get_all_similar_path_pairs_sorted_by_similarity();
	string initial_line =  format_initial_message(find_number_pair_found(similar_path_pairs));

	cout << initial_line << '\n';
	cout << Utils::LIMITER_PRINT << '\n';

	for(auto [path1, path2] : similar_path_pairs){
		process_similar_path_pair(path1,path2);
	}
}

Similarity_Explorer::Similarity_Explorer(Similarity_Table *_similarity_table, 
		int _limit_on_results, 
		string _pattern_to_match, 
		bool _both_path_need_to_match){
	similarity_table = _similarity_table;
	limit_on_results = _limit_on_results;
	pattern_to_match = _pattern_to_match;
	both_path_need_to_match_pattern = _both_path_need_to_match;
	explorer();
}
