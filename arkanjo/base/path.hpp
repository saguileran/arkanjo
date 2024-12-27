/*
This file expect the output of parser.cpp
This code filter the output only printing the files similar to files that contains a given pattern passed as argc
The code filter every file that has the pattern as a substring, so be carefull with duplications
*/

#ifndef PATH_HPP
#define PATH_HPP

#include <bits/stdc++.h> 
using namespace std;

class Path{
	//extension added on function name to run on ML TOOL
private:
	string JSON_EXTENSION = ".json";
	string BASE_INIT_STRING = "tmp";
	string SOURCE_STRING = "source";
	string HEADER_STRING = "header";
	string INFO_STRING = "info";
	char BAR = '/';

	vector<string> tokens;
	int position_start_relative_path;
	vector<string> split_path(string string_path);
	int find_position_start_relative_path();
	string build_string_path(vector<string> path);
	string build_base_path(string base);
	vector<string> get_tokens_from_relative_path();
	string remove_extension(string token);
public:
	bool is_empty();
	Path();
	Path(string string_path);
	string build_source_path();
	string build_header_path();
	string build_info_path();	
	string build_relative_path();	
	string build_function_name();
	vector<string> get_common_folders(Path path);
	bool contains_given_pattern(string pattern);
	bool operator<(const Path &path) const;
};


#endif
