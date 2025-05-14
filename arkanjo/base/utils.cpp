#include "utils.hpp"

#ifdef _WIN32
    #include "windows_utils.hpp"
#elif __linux__
    #include "linux_utils.hpp"
#elif __APPLE__
    #include "apple_utils.hpp" 
#endif

/**
 * @brief Ensures that a file stream is successfully opened
 * 
 * @param file Reference to the input file stream to check
 * @param file_name Name/path of the file being opened (for error message)
 * @throws Exits the program if file is not open
 * 
 * @note This function will terminate the program if the file is not open
 */
void Utils::ensure_file_is_open(std::ifstream &file, string file_name){
	if(!file.is_open()){
		cout << "Attempted to open file: " << file_name << " ";
		cout << "but a Error ocurred. Check if the file exist." << endl;
		exit(0);
	}
}

/**
 * @brief Reads a file line by line into a vector of strings
 * 
 * @param string_path Path to the file to read
 * @return vector<string> Contents of the file as a vector of strings (one per line)
 * @throws Exits program if file cannot be opened (via ensure_file_is_open)
 */
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

/**
 * @brief Writes content to a file at specified path
 * 
 * @param file_path Path where file should be written
 * @param content Vector of strings to write (each element becomes a line)
 * 
 * @note Creates parent directories if they don't exist
 */
void Utils::write_file_generic(string file_path, vector<string> content){
	std::ofstream fileout;
	create_parents_folder_of_file_path(file_path);
	fileout.open(file_path);

	for(auto line : content){
		fileout << line << '\n';
	}
	fileout.close();
}

/**
 * @brief Creates all parent directories for a given file path
 * 
 * @param file_path The full file path for which to create parent directories
 * 
 * @note Handles paths with '/' separators. Creates each directory in the path.
 */
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

/**
 * @brief Reads and parses a JSON file
 * 
 * @param string_path Path to the JSON file
 * @return Json::Value Parsed JSON content
 * @throws Exits program if file cannot be opened (via ensure_file_is_open)
 */
Json::Value Utils::read_json(string string_path){
	ifstream json_file(string_path,std::ifstream::binary);
	ensure_file_is_open(json_file,string_path);
	Json::Value json;
	json_file >> json;
	json_file.close();
	return json;
}

/**
 * @brief Checks if a file exists at the given path
 * 
 * @param file_path Path to check
 * @return bool True if file exists and is accessible, false otherwise
 */
bool Utils::does_file_exist(string file_path){
	if (FILE *file = fopen(file_path.c_str(), "r")) {
		fclose(file);
		return true;
	} else {
		return false;
	} 	
}

/**
 * @brief Determines if a path refers to a regular file
 * 
 * @param path Path to check
 * @return bool True if path is a regular file, false otherwise
 */
bool Utils::is_regular_file(string path){
	struct stat path_stat;
	auto path_c_str = path.c_str();
	stat(path_c_str,&path_stat);
	return S_ISREG(path_stat.st_mode);
}

/**
 * @brief Formats a message with ANSI color codes based on background darkness
 * 
 * @param message Text to colorize
 * @param color Color to apply
 * @return string Colorized message with reset code at the end
 * 
 * @note Automatically selects light or dark color variants based on background
 */
string Utils::format_colored_message(string message, COLOR color){
	if (UtilsOSDependable::is_bg_color_dark()){
		return COLOR_TOKENS_UTILS_LIGTH[color] + message + COLOR_TOKENS_UTILS_LIGTH[RESET];
	}
	else{
		return COLOR_TOKENS_UTILS_DARK[color] + message + COLOR_TOKENS_UTILS_DARK[RESET];
	}
}

/**
 * @brief Checks if a character is considered empty/whitespace
 * 
 * @param c Character to check
 * @return bool True if character is space or control character (<= 20), false otherwise
 */
bool Utils::is_empty_char(char c){
	if(c == ' '){
		return true;
	}
	if(c <= 20){
		return true;
	}
	return false;
}

/**
 * @brief Checks if a character is special (non-alphanumeric and not underscore)
 * 
 * @param c Character to check
 * @return bool True if character is special, false if alphanumeric or underscore
 */
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

/**
 * @brief Splits a string by a delimiter into tokens
 * 
 * @param s String to split
 * @param delimiter Character to split on
 * @return vector<string> Vector of tokens (empty tokens are omitted)
 */
vector<string> Utils::split_string(string s, char delimiter){
	string cur_token;
	vector<string> ret;
	for(auto c : s){
		if(c == delimiter){
			if(!cur_token.empty()){
				ret.push_back(cur_token);
			}
			cur_token = "";
		}else{
			cur_token.push_back(c);
		}
	}
	if(!cur_token.empty()){
		ret.push_back(cur_token);
	}
	return ret;
}