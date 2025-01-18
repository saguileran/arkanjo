/*
This file intends to create a script to read a directory with 
code in c and extract every function/struct of every .c file as a new file

Example of expected behaviour: 
There is a file example.c with functions a and b, will be create two new 
files: example/a.c and example/b.c

TODO: Doesn't work correct if the file has an incorrect bracket sequence, 
even if the bracket sequence is in a commentary
*/

#include <bits/stdc++.h>
#include "../base/utils.hpp"
using namespace std;

struct Line_content{
	int line_number;
	string content;
};

enum PROGRAMMING_LANGUAGE{
	C,
	JAVA
};

class FunctionBreaker{

	const vector<string> C_EXTENSIONS = { "c","h"};
	const vector<string> JAVA_EXTENSIONS =  { "java" };
	const vector<string> ALLOWED_EXTENSIONS = { "c","h","java" };
	const string SOURCE_PATH = "tmp/source";
	const string HEADER_PATH = "tmp/header";
	const string INFO_PATH =   "tmp/info";
	const int NUMBER_OF_LINES_BEFORE_FOR_FUNCTION_NAME = 7;
	const int C_RELEVANT_DEPTH = 0;
	const int JAVA_RELEVANT_DEPTH = 1;
	const bool IGNORE_EMPTY_FUNCTIONS = true;

	const bool ALLOW_STRUCTS = false;

	bool is_c_extension(string extension);

	bool is_java_extension(string extension);

	bool is_allowed_extension(string extension);

	string extract_extension(string file_path);

	set<array<int,3>> find_start_end_and_depth_of_brackets(vector<string> brackets_content);

	set<pair<int,int>> find_start_end_of_brackets_of_given_depth(vector<string> brackets_content, int depth);

	int find_position_first_open_bracket(string s);

	string extract_last_token_of_string(string s);

	Line_content build_line_code(int line_number, string content);

	vector<Line_content> get_lines_before_body_function(const vector<string> &file_content, int line_start_body_function, int pos_bracket);

	vector<Line_content> remove_parenteses_at_the_end_of_the_scope(vector<Line_content> code);

	vector<Line_content> remove_content_until_find_parenteses_at_the_end(vector<Line_content> code);

	vector<Line_content> remove_parameters_of_declaration_c(vector<Line_content> code);

	vector<Line_content> remove_parameters_of_declaration_java(vector<Line_content> code);

	vector<Line_content> remove_parameters_of_declaration(vector<Line_content> code, PROGRAMMING_LANGUAGE programming_language);

	pair<string,int> extract_function_name_and_line_from_declaration(const vector<string> &file_content, int line_start_body_function, PROGRAMMING_LANGUAGE programming_language);

	string build_source_path(string relative_path, string function_name);

	string build_header_path(string relative_path, string function_name);

	string build_info_path(string relative_path, string function_name);

	vector<string> build_function_content(int start_number_line, int end_number_line,const vector<string> &file_content);

	bool is_body_function_empty(int start_number_line, int end_number_line,const vector<string> &file_content);

	void create_source_file(int start_number_line, int end_number_line, string relative_path, string function_name, const vector<string> &file_content);

	void create_header_file(int start_number_line, int line_declaration, string relative_path, string function_name, const vector<string> &file_content);

	/*This creates a json file*/
	void create_info_file(int line_declaration, int start_number_line, int end_number_line, string relative_path, string function_name);

	void process_function(int start_number_line, int end_number_line, string relative_path, const vector<string> &file_content, PROGRAMMING_LANGUAGE programming_language);

	string file_path_from_folder_path(string file_path, string folder_path);

	void file_breaker_c(string file_path, string folder_path);

	void file_breaker_java(string file_path, string folder_path);

	void file_breaker(string file_path, string folder_path);

	void function_breaker(string folder_path);

	public:
	FunctionBreaker(string folder_path);
};
