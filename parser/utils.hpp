#ifndef UTILS_HPP
#define UTILS_HPP

#include <bits/stdc++.h> 
#include <jsoncpp/json/json.h>

using namespace std;

namespace Utils{

	const string LIMITER_PRINT = "---------------------";

	const vector<string> COLOR_TOKENS_UTILS = {
		"\033[0m", //RESET
		"\033[31m", //RED
		"\033[32m", //GREEN
		"\033[33m", //YELLOW
		"\033[33m", //BLUE
		"\033[35m", //MAGENTA
		"\033[36m", //CYAN
		"\033[37m", //GRAY
		"\033[97m", //WHITE
		"\033[33;1m", //BRIGHT_YELLOW
	};
	
	enum COLOR{
		RESET,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		GRAY,
		WHITE,
		BRIGHT_YELLOW
	};

	void ensure_file_is_open(std::ifstream &file, string file_name);
	vector<string> read_file_generic(string string_path);
	Json::Value read_json(string string_path);

	string format_colored_message(string message, COLOR color);
};

#endif

