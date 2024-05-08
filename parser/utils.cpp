
#include "utils.hpp"

void Utils::ensure_file_is_open(std::ifstream &file, string file_name){
	if(!file.is_open()){
		cout << "Attempted to open file: " << file_name << " ";
		cout << "but a Error ocurred. Check if the file exist." << endl;
		exit(0);
	}
}

vector<string> Utils::read_file_generic(string string_path){
	std::ifstream filein;
	string line;
	vector<string> ret;
	filein.open(string_path);
	ensure_file_is_open(filein,string_path);
	while(getline(filein,line)){
		ret.push_back(line);
	}
	filein.close();
	return ret;
}

Json::Value Utils::read_json(string string_path){
	ifstream json_file(string_path,std::ifstream::binary);
	ensure_file_is_open(json_file,string_path);
	Json::Value json;
	json_file >> json;
	json_file.close();
	return json;
}

string Utils::format_colored_message(string message, COLOR color){
	return COLOR_TOKENS_UTILS[RESET] + message + COLOR_TOKENS_UTILS[color];
}


