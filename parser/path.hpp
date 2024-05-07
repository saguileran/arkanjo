/*
This file expect the output of parser.cpp
This code filter the output only printing the files similar to files that contains a given pattern passed as argc
The code filter every file that has the pattern as a substring, so be carefull with duplications
*/

#ifndef PATH_SOURCE
#define PATH_SOURCE

#include <bits/stdc++.h> 
using namespace std;

class Path{
	//extension added on function name to run on ML TOOL
private:
	const string EXTENSION = ".c";
	const string JSON_EXTENSION = ".json";
	const string BASE_INIT_STRING = "tmp";
	const string SOURCE_STRING = "source";
	const string HEADER_STRING = "header";
	const string INFO_STRING = "info";
	const char BAR = '/';

	vector<string> tokens;
	int position_start_relative_path;
	vector<string> split_path(string string_path);
	int find_position_start_relative_path();
	string build_string_path(vector<string> path);
	string build_base_path(string base);

public:
	Path(string string_path);
	string build_source_path();
	string build_header_path();
	string build_info_path();	
	string build_relative_path();	
	string build_function_name();
};


#endif
