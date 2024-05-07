
#include "path.hpp" 
using namespace std;

vector<string> Path::split_path(string string_path){
	string aux = "";
	vector<string> ret;
	for(auto c : string_path){
		if(c == BAR){
			ret.push_back(aux);
			aux = "";
		}else{
			aux += c;
		}
	}
	if(!aux.empty()){
		ret.push_back(aux);
	}
	return ret;
}

int Path::find_position_start_relative_path(){
	int sz = tokens.size();
	int ret = sz;
	for(int i = 0; i < sz-1; i++){
		if(tokens[i] == BASE_INIT_STRING && tokens[i+1] == SOURCE_STRING){
			ret = i+2;
		}
	}
	assert(ret != sz && "PATH NOT VALID FOR THE TOOL");
	return ret;
}

Path::Path(string string_path){
	tokens = split_path(string_path);
	position_start_relative_path = find_position_start_relative_path();
}

string Path::build_string_path(vector<string> path){
	string string_path;
	int sz = path.size();
	for(int i = 0; i < sz; i++){
		string_path += path[i];
		if(i != sz-1){
			string_path += BAR;
		}
	}
	return string_path;
}

string Path::build_base_path(string base){
	vector<string> path = tokens;
	int pos_change = position_start_relative_path-1;
	path[pos_change] = base;
	string string_path = build_string_path(path);
	return string_path;
}

string Path::build_source_path(){
	return build_base_path(SOURCE_STRING);
}

string Path::build_header_path(){
	return build_base_path(HEADER_STRING);
}

string Path::build_info_path(){
	string ret = build_base_path(INFO_STRING);
	int sz = EXTENSION.size();
	for(int i = 0; i < sz; i++){
		ret.pop_back();
	}
	ret += JSON_EXTENSION;
	return ret;
}

string Path::build_relative_path(){
	vector<string> path = tokens;
	path.pop_back();
	int to_remove = position_start_relative_path;
	reverse(path.begin(),path.end());
	for(int i = 0; i < to_remove; i++){
		path.pop_back();
	}
	reverse(path.begin(),path.end());
	string string_path = build_string_path(path);
	return string_path;
}

string Path::build_function_name(){
	string function_name = tokens.back();
	int sz = EXTENSION.size();
	for(int i = 0; i < sz; i++){
		function_name.pop_back();
	}
	return function_name;
}


