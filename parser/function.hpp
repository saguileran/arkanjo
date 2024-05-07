
#include <bits/stdc++.h> 
//WARNING THIS IMPORT MAYBE ONLY WORKS IN UBUNTU, SEE HERE: https://github.com/stardust95/TinyCompiler/issues/2
#include <jsoncpp/json/json.h>

#include "path.hpp"
using namespace std;

class Function{
	private:
		const string LINE_DECLARATION_JSON = "line_declaration";
		const string START_NUMBER_LINE_JSON = "start_number_line";
		const string END_NUMBER_LINE_JSON = "end_number_line";

		Path* path;
		vector<string> content;
		vector<string> header;
		int start_number_line;
		int line_declaration;
		int end_number_line;

		vector<string> read_file_generic(string string_path);
		Json::Value read_json(string string_path);
		void read_content();
		void read_header();
		void read_info();
	public:
		Function(Path *_path);
		pair<int,int> get_scope_function_in_file();
		vector<string> get_header();
		vector<string> build_all_content();
};
