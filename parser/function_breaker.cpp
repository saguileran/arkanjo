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
#include <sys/stat.h>
using namespace std;

const vector<string> ALLOWED_EXTENSIONS = { "c","h" };
const string SOURCE_TO_PATH = "tmp/source";
const int MKDIR_FLAG = 0700;
const int NUMBER_OF_LINES_BEFORE_FOR_FUNCTION_NAME = 10;

vector<string> read_file_as_vector(string file_path){
	std::ifstream filein;
	string line;
	vector<string> ret;

	filein.open(file_path);
	while(getline(filein,line)){
		ret.push_back(line);
	}
	filein.close();

	return ret;
}

void create_parents_folder_of_file_path(string file_path){
	vector<string> parents;
	for(size_t i = 0; i < file_path.size(); i++){
		if(file_path[i] == '/'){
			string s = "";
			for(size_t j = 0; j < i; j++){
				s += file_path[j];
			}
			parents.push_back(s);
		}
	}
	for(auto folder : parents){
		const char *cfolder = folder.c_str();
		mkdir(cfolder,MKDIR_FLAG);
	}
}

void write_file_from_vector(string file_path, vector<string> content){
	std::ofstream fileout;
	create_parents_folder_of_file_path(file_path);
	fileout.open(file_path);

	for(auto line : content){
		fileout << line << '\n';
	}

	fileout.close();
}

bool is_empty_char(char c){
	if(c == ' '){
		return true;
	}
	if(c <= 20){
		return true;
	}
	return false;
}

bool is_special_char(char c){
	if(c >= 'a' && c <= 'z'){
		return false;
	}
	if(c >= 'A' && c <= 'Z'){
		return false;
	}
	if(c >= '0' && c <= '9'){
		return false;
	}
	if(c == '_'){
		return false;
	}
	return true;
}

bool contains_special_char(string s){
	for(auto c : s){
		if(is_special_char(c)){
			return true;
		}
	}
	return false;
}

set<pair<int,int>> find_start_end_of_global_brackets(vector<string> brackets_content){
	set<pair<int,int>> start_ends;
	int open_brackets = 0;
	int ini = -1;
	auto process_open = [&](int line_number){
		open_brackets++;
		if(open_brackets == 1){
			ini = line_number;
		}
	};
	auto process_close = [&](int line_number){
		open_brackets--;
		if(open_brackets <= -1){
			open_brackets = 0;
		}
		if(open_brackets == 0 && ini != -1){
			start_ends.insert({ini,line_number});
			ini = -1;
		}
	};
	for(size_t i = 0; i < brackets_content.size(); i++){
		auto line = brackets_content[i];
		for(auto c : line){
			if(c == '{'){
				process_open(i);
			}
			if(c == '}'){
				process_close(i);
			}
		}
	}
	return start_ends;
}

int find_position_first_open_bracket(string s){
	for(size_t i = 0; i < s.size(); i++){
		char c = s[i];
		if(c == '(' || c == '{'){
			return i;
		}
	}
	return -1;
}

string extract_last_token_of_string(string s){
	vector<string> tokens;
	string cur_token = "";
	for(size_t i = 0; i < s.size(); i++){
		char c = s[i];
		if( is_empty_char(c)){
			if(!cur_token.empty()){
				tokens.push_back(cur_token);
			}
			cur_token = "";
		}else{
			cur_token += c;
		}
	}
	if(!cur_token.empty()){
		tokens.push_back(cur_token);
	}

	
	while(!tokens.empty() && contains_special_char(tokens.back())){
		tokens.pop_back();
	}

	if(tokens.empty()){
		return "";
	}

	return tokens.back();
}

string concat_lines_before_body_function(const vector<string> &file_content, int line_start_body_function, int pos_bracket){	
	string ret = file_content[line_start_body_function];
	int until = max(0,line_start_body_function-NUMBER_OF_LINES_BEFORE_FOR_FUNCTION_NAME);
	for(int i = line_start_body_function-1; i >= until; i--){
		pos_bracket += file_content[i].size();
		ret = file_content[i] + ret;
	}
	//remove everything after {
	while(int(ret.size()) > pos_bracket){
		ret.pop_back();
	}
	while(!ret.empty() && is_empty_char(ret.back())){
		ret.pop_back();
	}
	return ret;
}

string remove_parameters_of_declaration(string code){
	if(code.empty() || code.back() != ')'){
		return code;
	}
	int count_close_parenteses = 0;
	while(!code.empty()){
		if(code.back() == ')'){
			count_close_parenteses++;
		}
		if(code.back() == '('){
			count_close_parenteses--;
		}
		code.pop_back();
		if(count_close_parenteses == 0){
			break;
		}
	}
	return code;
}

string extract_function_name_from_declaration(const vector<string> &file_content, int line_start_body_function){
	int pos = find_position_first_open_bracket(file_content[line_start_body_function]);
	string code_before_bracket = concat_lines_before_body_function(file_content, line_start_body_function,pos);
	string code = remove_parameters_of_declaration(code_before_bracket);
	string ret = extract_last_token_of_string(code);
	return ret;
}

string extract_extension(string file_path){
	string extension = "";
	int pos_last_dot = -1;
	for(size_t i = 0; i < file_path.size(); i++){
		if(file_path[i] == '.'){
			pos_last_dot = i;
		}
	}
	if(pos_last_dot == -1){
		return extension;
	}
	for(size_t i = pos_last_dot+1; i < file_path.size(); i++){
		extension += file_path[i];
	}
	return extension;
}

string build_final_path(string relative_path, string function_name){
	string extension = extract_extension(relative_path);
	string final_path = SOURCE_TO_PATH + relative_path + "/";
	final_path += function_name + "." + extension;
	return final_path;
}

void process_function(int start_number_line, int end_number_line, string relative_path, const vector<string> &file_content){
	string first_line = file_content[start_number_line];
	string function_name = extract_function_name_from_declaration(file_content,start_number_line);

	if(function_name.empty()){
		return;
	}

	string path = build_final_path(relative_path, function_name);
	vector<string> function_content;
	for(int i = start_number_line; i <= end_number_line; i++){
		function_content.push_back(file_content[i]);
	}

	write_file_from_vector(path, function_content);
}

string file_path_from_folder_path(string file_path, string folder_path){
	string ret = "";
	for(size_t i = folder_path.size(); i < file_path.size(); i++){
		ret += file_path[i];
	}
	return ret;
}


bool is_allowed_extension(string extension){
	for(auto allowed_extension : ALLOWED_EXTENSIONS){
		if(extension == allowed_extension){
			return true;
		}
	}
	return false;
}

void file_breaker(string file_path, string folder_path){
	string extension = extract_extension(file_path);
	string relative_path = file_path_from_folder_path(file_path, folder_path);

	if(!is_allowed_extension(extension)){
		return;
	}

	vector<string> file_content = read_file_as_vector(file_path);
	set<pair<int,int>> start_end_of_functions = find_start_end_of_global_brackets(file_content);

	for(auto [start_line, end_line] : start_end_of_functions){
		process_function(start_line,end_line,relative_path, file_content);
	}
}

void function_breaker(string folder_path){
	for(const auto &dirEntry: std::filesystem::recursive_directory_iterator(folder_path)){
		string file_path = dirEntry.path().string();
		file_breaker(file_path,folder_path);
	}
}

int main(int argc, char *argv[]){
	if(argc <= 1){
		cout << "Required folder path to process was not given" << endl;
		return 0;
	}
	string folder_path(argv[1]);
	function_breaker(folder_path);

	return 0;
}
