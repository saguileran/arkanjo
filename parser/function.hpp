#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <bits/stdc++.h> 
//WARNING THIS IMPORT MAYBE ONLY WORKS IN UBUNTU, SEE HERE: https://github.com/stardust95/TinyCompiler/issues/2
#include <jsoncpp/json/json.h>

#include "path.hpp"
#include "utils.hpp"
using namespace std;

class Function{
	private:
		string LINE_DECLARATION_JSON = "line_declaration";
		string START_NUMBER_LINE_JSON = "start_number_line";
		string END_NUMBER_LINE_JSON = "end_number_line";

		Path path;
		vector<string> content;
		vector<string> header;
		int start_number_line;
		int line_declaration;
		int end_number_line;
	
		void read_content();
		void read_header();
		void read_info();
	public:
		Function(Path _path);
		pair<int,int> get_scope_function_in_file();
		vector<string> get_header();
		vector<string> build_all_content();
};

#endif
