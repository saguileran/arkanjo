#include "function.hpp"

void Function::read_content(){
	string source_path = path.build_source_path();
	content = Utils::read_file_generic(source_path);
}	

void Function::read_header(){
	string header_path = path.build_header_path();
	header = Utils::read_file_generic(header_path);
}

void Function::read_info(){
	string info_path = path.build_info_path();
	Json::Value info = Utils::read_json(info_path);
	line_declaration = info[LINE_DECLARATION_JSON].asInt();
	start_number_line = info[START_NUMBER_LINE_JSON].asInt();
	end_number_line = info[END_NUMBER_LINE_JSON].asInt();
}

Function::Function(Path _path){
	path = _path;
	if(path.is_empty()){
		return;
	}
	read_content();
	read_header();
	read_info();
}

pair<int,int> Function::get_scope_function_in_file(){
	return make_pair(line_declaration,end_number_line);
}

vector<string> Function::get_header(){
	return header;
}

vector<string> Function::build_all_content(){
	
	vector<string> ret;
	//the last line of header should merge with the first line of content
	for(auto line : header){
		ret.push_back(line);
	}
	for(int i = 0; i < int(content.size()); i++){
		auto line = content[i];
		if(i >= 1){
			ret.push_back(line);
		}else{
			ret.back() += line;
		}
	}
	return ret;
}

void Function::print_basic_info(){
	string function_message = FUNCTION_PREFIX_PRINT + path.build_function_name();
	string relative_message = RELATIVE_PATH_PRINT + path.build_relative_path();
	string start_message = LINE_DECLARATION_PRINT + to_string(line_declaration);
	string end_message = END_DECLARATION_PRINT + to_string(end_number_line);
	
	cout << '\n';
	cout << LIMITER_PRINT << '\n';
	cout << Utils::format_colored_message(function_message, Utils::YELLOW) << '\n';
	cout << Utils::format_colored_message(function_message, Utils::GREEN) << '\n';
	cout << Utils::format_colored_message(start_message, Utils::WHITE) << '\n';
	cout << Utils::format_colored_message(end_message, Utils::WHITE) << '\n';
	cout << LIMITER_PRINT << '\n';
	cout << '\n';
}
