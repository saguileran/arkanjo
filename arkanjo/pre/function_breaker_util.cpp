#include "function_breaker_util.hpp"

// TODO Refactor, refactor this
namespace {
	int find_position_first_open_bracket(string s){
		for(size_t i = 0; i < s.size(); i++){
			char c = s[i];
			if(c == '{'){
				return i;
			}
		}
		return -1;
	}

	vector<string> build_function_content(int start_number_line, int end_number_line,const vector<string> &file_content){
		string first_line = file_content[start_number_line];
		int to_remove = find_position_first_open_bracket(first_line);

		vector<string> function_content;
		reverse(first_line.begin(),first_line.end());
		for(int i = 0; i < to_remove; i++){
			first_line.pop_back();
		}
		reverse(first_line.begin(),first_line.end());
		function_content.push_back(first_line);
		for(int i = start_number_line+1; i <= end_number_line; i++){
			function_content.push_back(file_content[i]);
		}
		return function_content;
	}

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

string build_source_path(string relative_path, string function_name){
	string extension = extract_extension(relative_path);
	string final_path = SOURCE_PATH + relative_path + "/";
	final_path += function_name + "." + extension;
	return final_path;
}

string build_header_path(string relative_path, string function_name){
	string extension = extract_extension(relative_path);
	string final_path = HEADER_PATH + relative_path + "/";
	final_path += function_name + "." + extension;
	return final_path;
}

string build_info_path(string relative_path, string function_name){
	string extension = extract_extension(relative_path);
	string final_path = INFO_PATH + relative_path + "/";
	final_path += function_name + ".json";
	return final_path;
}

void create_source_file(int start_number_line, int end_number_line, string relative_path, string function_name, const vector<string> &file_content){
	string path = build_source_path(relative_path, function_name);
	vector<string> function_content = build_function_content(start_number_line, end_number_line, file_content);
	Utils::write_file_generic(path, function_content);
}

void create_header_file(int start_number_line, int line_declaration, string relative_path, string function_name, const vector<string> &file_content){
	string path = build_header_path(relative_path, function_name);
	vector<string> function_content;
	for(int i = line_declaration; i < start_number_line; i++){
		function_content.push_back(file_content[i]);
	}

	string first_line = file_content[start_number_line];
	int to_keep = find_position_first_open_bracket(first_line);
	while(int(first_line.size()) > to_keep){
		first_line.pop_back();
	}
	function_content.push_back(first_line);

	Utils::write_file_generic(path, function_content);
}

/*This creates a json file*/
void create_info_file(int line_declaration, int start_number_line, int end_number_line, string relative_path, string function_name){
	vector<string> content;
	content.push_back("{\n");
	content.push_back("\"file_name\":\"" + relative_path + "\",\n");
	content.push_back("\"function_name\":\"" + function_name + "\",\n");
	content.push_back("\"line_declaration\":" + to_string(line_declaration) + ",\n");
	content.push_back("\"start_number_line\":" + to_string(start_number_line) + ",\n");
	content.push_back("\"end_number_line\":" + to_string(end_number_line) + "\n");
	content.push_back("}\n");
	string path = build_info_path(relative_path, function_name);
	Utils::write_file_generic(path, content);
}

