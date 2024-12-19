#include "preprocessor.hpp"

void Preprocessor::preprocess(){
	string path,similarity;

	cout << PROJECT_PATH_MESSAGE << '\n';
	cin >> path;

	cout << MINIMUM_SIMILARITY_MESSAGE << '\n';
	cin >> similarity;
	
	string command_breaker = "./breaker " + path;
	string command_tool = "python3 -W ignore third-party/duplicate-code-detection-tool/duplicate_code_detection.py -d tmp/source > output_tool.txt";
	string command_parser_output = "./parser " + similarity + " < output_tool.txt > output_parsed.txt";
	
	system(command_breaker.c_str());
	system(command_tool.c_str());
	system(command_parser_output.c_str());
}
