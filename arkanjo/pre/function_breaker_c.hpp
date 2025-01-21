// Defines the flow of parsing a source cpp file in multiples functions

#ifndef FUNCTION_BREAKER_C_HPP
#define FUNCTION_BREAKER_C_HPP

#include <bits/stdc++.h>
#include "../base/utils.hpp"
#include "function_breaker_util.hpp"

class FunctionBreakerC{

	const int NUMBER_OF_LINES_BEFORE_FOR_FUNCTION_NAME = 7;
	const int C_RELEVANT_DEPTH = 0;
	const bool IGNORE_EMPTY_FUNCTIONS = true;

	const bool ALLOW_STRUCTS = false;

	vector<string> file_content;
	vector<vector<bool>> mask_valid;

	bool is_define(int line, int pos);
	
	// Only works if the code is compilable. I do have grant any 
	// ensurances if the source code does not compile
	void filter_mask_commentaries_and_defines(vector<vector<bool>>& mask);

	vector<vector<bool>> build_mask_valid_code();

	set<array<int,5>> find_start_end_and_depth_of_brackets();

	set<array<int,4>> find_start_end_of_brackets_of_given_depth();

	string extract_last_token_of_string(string s);

	Line_content build_line_code(int line_number, string content);

	vector<Line_content> get_lines_before_body_function(int line_start_body_function, int pos_bracket);

	vector<Line_content> remove_parenteses_at_the_end_of_the_scope(vector<Line_content> code);

	vector<Line_content> remove_content_until_find_parenteses_at_the_end(vector<Line_content> code);

	vector<Line_content> remove_parameters_of_declaration(vector<Line_content> code);

	pair<string,int> extract_function_name_and_line_from_declaration(int line_start_body_function, int end_column);

	vector<string> build_function_content(int start_number_line, int start_column, int end_number_line, int end_column);

	int find_position_first_open_bracket(string s);

	vector<string> build_header_content(int start_number_line, int line_declaration, string relative_path, string function_name);

	bool is_body_function_empty(int start_number_line, int start_column, int end_number_line, int end_column);

	void process_function(int start_number_line, int start_column, int end_number_line, int end_column, string relative_path);

	string file_path_from_folder_path(string file_path, string folder_path);

	void file_breaker_c(string file_path, string folder_path);

public:
	FunctionBreakerC(string file_path, string folder_path);

};

#endif
