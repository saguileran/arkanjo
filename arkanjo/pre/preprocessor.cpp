#include "preprocessor.hpp"

void Preprocessor::save_current_run_params(string path){
	vector<string> config_content;

	string path_message = PATH_MESSAGE + path;

	auto end = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	string time_message = TIME_MESSAGE + std::ctime(&end_time);

	config_content.push_back(path_message);
	config_content.push_back(time_message);

	Utils::write_file_generic(Config::config()->getBasePath() + "/" + CONFIG_PATH,config_content);
}

pair<string,double> Preprocessor::read_parameters(){
	cout << INITIAL_MESSAGE << '\n';
	string path,similarity_message;

	cout << PROJECT_PATH_MESSAGE << '\n';
	cin >> path;

	cout << MINIMUM_SIMILARITY_MESSAGE << '\n';
	cin >> similarity_message;
	double similarity = stod(similarity_message);
	return {path,similarity};
}

void Preprocessor::preprocess(string path, double similarity){
	cout << BREAKER_MESSAGE << '\n';

	Config *config = Config::config();
	string base_path = config->getBasePath();

	string command_rm_tmp = "rm -r -f " + base_path + "/";
	system(command_rm_tmp.c_str());
	FunctionBreaker function_breaker(path);


	cout << DUPLICATION_MESSAGE << '\n';

	string command_tool = "python3 -W ignore third-party/duplicate-code-detection-tool/duplicate_code_detection.py -d ";
	command_tool += base_path;
	command_tool += "/source > ";
	command_tool += base_path;
	command_tool += "/output_tool.txt";

	system(command_tool.c_str());

	cout << SAVING_MESSAGE << '\n';

	Parser parser(base_path+"/output_tool.txt",base_path+"/output_parsed.txt",similarity);

	save_current_run_params(path);

	cout << END_MESSAGE << '\n';
}

Preprocessor::Preprocessor(bool force_preprocess){
	if(force_preprocess || !Utils::does_file_exist(CONFIG_PATH)){
		auto [path,similarity] = read_parameters();
		preprocess(path,similarity);
	}
}

Preprocessor::Preprocessor(bool force_preprocess, string path, double similarity){
	if(force_preprocess || !Utils::does_file_exist(CONFIG_PATH)){
		preprocess(path,similarity);
	}
}
