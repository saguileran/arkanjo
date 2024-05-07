#ifndef UTILS_HPP
#define UTILS_HPP

#include <bits/stdc++.h> 
#include <jsoncpp/json/json.h>

using namespace std;

namespace Utils{
	void ensure_file_is_open(std::ifstream &file, string file_name);
	vector<string> read_file_generic(string string_path);
	Json::Value read_json(string string_path);
};

#endif

