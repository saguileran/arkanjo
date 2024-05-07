/*
This file expect the output of parser.cpp
This code filter the output only printing the files similar to files that contains a given pattern passed as argc
The code filter every file that has the pattern as a substring, so be carefull with duplications
*/

#include <bits/stdc++.h> 
//WARNING THIS IMPORT MAYBE ONLY WORKS IN UBUNTU, SEE HERE: https://github.com/stardust95/TinyCompiler/issues/2
#include <jsoncpp/json/json.h>

#include "path.hpp"
#include "function.hpp"
using namespace std;

const string example = "/home/luan/linux/test-duplication-code/parser/tmp/source/bios_parser.c/bios_parser_create.c";
	
int main(){
	Path path_source(example);
	
	cout << path_source.build_source_path() << '\n';
	cout << path_source.build_header_path() << '\n';
	cout << path_source.build_info_path() << '\n';
	cout << path_source.build_relative_path() << '\n';
	cout << path_source.build_function_name() << '\n';


	Function function(&path_source);
	//test of get_head
	{
		vector<string> ret = function.get_header();
		for(auto x : ret){
			cout << x << '\n';
		}
		cout << "-----\n";;
	}
	{
		vector<string> ret = function.build_all_content();
		for(auto x : ret){
			cout << x << '\n';
		}
		cout << "----\n";
	}

	auto [INI,FIM] = function.get_scope_function_in_file();
	cout << INI << ' ' << FIM << '\n';
	
	return 0;
}

