#include "function.hpp"

vector<string> Function::read_file_generic(string string_path){
	std::ifstream filein;
	string line;
	vector<string> ret;
	filein.open(string_path);
	while(getline(filein,line)){
		ret.push_back(line);
	}
	filein.close();
	return ret;
}

Json::Value Function::read_json(string string_path){
	ifstream json_file(string_path,std::ifstream::binary);
	Json::Value json;
	json_file >> json;
	json_file.close();
	return json;
}

void Function::read_content(){
	string source_path = path->build_source_path();
	content = read_file_generic(source_path);
}	

void Function::read_header(){
	string header_path = path->build_header_path();
	header = read_file_generic(header_path);
}

void Function::read_info(){
	string info_path = path->build_info_path();
	Json::Value info = read_json(info_path);
	line_declaration = info[LINE_DECLARATION_JSON].asInt();
	start_number_line = info[START_NUMBER_LINE_JSON].asInt();
	end_number_line = info[END_NUMBER_LINE_JSON].asInt();
}

Function::Function(Path *_path){
	path = _path;
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
	for(auto line : header){
		ret.push_back(line);
	}
	for(auto line : content){
		ret.push_back(line);
	}
	return ret;
}

