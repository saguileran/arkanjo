#include "preprocessor.hpp"

void Preprocessor::save_current_run_params(string path){
	vector<string> config_content;

	string path_message = PATH_MESSAGE + path;

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	string time_message = TIME_MESSAGE + std::ctime(&end_time);

	config_content.push_back(path_message);
	config_content.push_back(time_message);

	Utils::write_file_generic(CONFIG_PATH,config_content);
}

void Preprocessor::preprocess(){
	cout << INITIAL_MESSAGE << '\n';
	string path,similarity_message;

	cout << PROJECT_PATH_MESSAGE << '\n';
	cin >> path;

	cout << MINIMUM_SIMILARITY_MESSAGE << '\n';
	cin >> similarity_message;
	double similarity = stod(similarity_message);
	
	cout << BREAKER_MESSAGE << '\n';
	
	string command_rm_tmp = "rm -r -f tmp/";
	system(command_rm_tmp.c_str());
	FunctionBreaker function_breaker(path);


	cout << DUPLICATION_MESSAGE << '\n';
	
	string command_tool = "python3 -W ignore third-party/duplicate-code-detection-tool/duplicate_code_detection.py -d ./tmp/source > tmp/output_tool.txt";
	system(command_tool.c_str());

	cout << SAVING_MESSAGE << '\n';

	Parser parser("tmp/output_tool.txt","tmp/output_parsed.txt",similarity);

	save_current_run_params(path);

	cout << END_MESSAGE << '\n';
}

Preprocessor::Preprocessor(bool force_preprocess){
	if(force_preprocess || !Utils::does_file_exist(CONFIG_PATH)){
		preprocess();
	}
}
