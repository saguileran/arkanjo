
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

void Utils::write_file_generic(string file_path, vector<string> content){
	std::ofstream fileout;
	create_parents_folder_of_file_path(file_path);
	fileout.open(file_path);

	for(auto line : content){
		fileout << line << '\n';
	}

	fileout.close();
}

void Utils::create_parents_folder_of_file_path(string file_path){
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

Json::Value Utils::read_json(string string_path){
	ifstream json_file(string_path,std::ifstream::binary);
	ensure_file_is_open(json_file,string_path);
	Json::Value json;
	json_file >> json;
	json_file.close();
	return json;
}

string Utils::format_colored_message(string message, COLOR color){
	return COLOR_TOKENS_UTILS[color] + message + COLOR_TOKENS_UTILS[RESET];
}

bool Utils::is_empty_char(char c){
	if(c == ' '){
		return true;
	}
	if(c <= 20){
		return true;
	}
	return false;
}

bool Utils::is_special_char(char c){
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
