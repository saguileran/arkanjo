// TODO - line declaration extraction does not work really well to extract definition
// because of comments or define in the middle of definition

#include "function_breaker_c.hpp"

bool FunctionBreakerC::is_define(vector<string>& brackets_content, int line, int pos){
	int line_size = brackets_content.size();
	// does not fit the #define token
	if(pos+7 > line_size) return false; 		
	// match the token
	string token = "#define";
	bool match = true;
	for(int j = 0; j < 7; j++){
		match &= brackets_content[line][pos+j] == token[j];
	}
	return match;
}

// Only works if the code is compilable. I do have grant any 
// ensurances if the source code does not compile
void FunctionBreakerC::filter_mask_commentaries_and_defines(vector<string>& brackets_content,vector<vector<bool>>& mask){
	// aqui tbm tem que lidar com string literal, ie, "#define" nao eh define a
	// eh "//" nao eh commentario
	int number_lines = brackets_content.size();
	bool is_open_block_comment = false;
	bool is_open_define = false;
	bool is_open_quotation_marks = false;
	bool is_open_line_comment = false;

	for(int i = 0; i < number_lines; i++){
		auto& line = brackets_content[i];
		auto& mask_line = mask[i];
		int line_size = line.size();

		if(is_open_define){
			for(int j = 0; j < line_size; j++){
				mask_line[j] = false;
			}
			// if the last token is to continue the define
			if(line.back() != '\\'){
				is_open_define = false;
			}
			continue;
		}

		if(is_open_line_comment){
			for(int j = 0; j < line_size; j++){
				mask_line[j] = false;
			}
			// if the last token is to continue the define
			if(line.back() != '\\'){
				is_open_line_comment = false;
			}
			continue;
		}

		for(int j = 0; j < line_size; j++){
			if(is_open_block_comment){
				mask_line[j] = false;
				// if the block line comes to an end
				if(j+1 < line_size && line[j] == '*' && line[j+1] == '/'){
					j++;
					mask_line[j] = false;
					is_open_block_comment = false;
				}
				continue;
			}

			if(is_open_quotation_marks){
				mask_line[j] = false;
				// TODO should I take a look on ""s ?
				if(line[j] == '"'){
					is_open_quotation_marks = false;
				}else if(line[j] == '\\'){
					if(j == line_size-1){
						break;
					}else{
						j++;
						mask_line[j] = false;
					}
				}
				continue;
			}

			if(line[j] == '\''){
				assert(j+1 < line_size && 
					   "source code does not compile, ' open but not closed");
				mask_line[j] = false;
				j++;
				if(line[j] == '\\'){
					assert(j+2 < line_size && line[j+2] == '\'' &&
					   	   "source code does not compile, ' open but not closed");
					mask_line[j] = false;
					j++;
				}else{
					assert(j+1 < line_size && line[j+1] == '\'' &&
					   	   "source code does not compile, ' open but not closed");
				}
				mask_line[j] = false;
				j++;
				mask_line[j] = false;
				continue;
			}

			if(line[j] == '"'){
				is_open_quotation_marks = true;
				mask_line[j] = false;
				continue;
			}

			if(line[j] == '/'){
				if(j == line_size-1){
					continue;
				}

				if(line[j+1] == '/'){
					for(int k = j; k < line_size; k++){
						mask_line[k] = false;
					}
					// find line comment, everything after is comment and 
					// break the iteration on the current line
					is_open_line_comment = line.back() == '\\';
					break;
				}

				if(line[j+1] == '*'){
					mask_line[j] = false;
					j++;
					mask_line[j] = false;
					is_open_block_comment = true;
					continue;
				}
			}

			if(is_define(brackets_content,i,j)){
				for(int k = j; k < line_size; k++){
					mask_line[k] = false;
				}
				// find #define, everything after is comment and 
				// break the iteration on the current line
				is_open_define = line.back() == '\\';
				break;
			}
		}
	}

	assert(is_open_block_comment == false && 
			"source code does not compile, open block comment");
	assert(is_open_quotation_marks == false &&
			"source code does not compile, open quotation marks");
}

// the exactly same size of the input source, the character will be 1 if it is not in a commentary nor a #define's
vector<vector<bool>> FunctionBreakerC::build_mask_valid_code(vector<string> brackets_content){
	vector<vector<bool>> mask(brackets_content.size());
	for(int i = 0; i < (int)brackets_content.size(); i++){
		mask[i] = vector<bool>(brackets_content[i].size(),true);
	}
	filter_mask_commentaries_and_defines(brackets_content,mask);
	return mask;
}

set<array<int,5>> FunctionBreakerC::find_start_end_and_depth_of_brackets(vector<string> brackets_content){
	vector<vector<bool>> mask_valid = build_mask_valid_code(brackets_content);
	set<array<int,5>> start_ends;
	int open_brackets = 0;

	vector<pair<int,int>> not_processed_open_brackets;
	auto process_open = [&](int line_number, int column){
		open_brackets++;
		not_processed_open_brackets.push_back({line_number,column});
	};
	auto process_close = [&](int line_number, int column){
		open_brackets--;
		if(open_brackets <= -1){
			open_brackets = 0;
		}else{
			auto [matched_line,matched_column]= not_processed_open_brackets.back();
			not_processed_open_brackets.pop_back();
			int depth_of_open = not_processed_open_brackets.size();
			start_ends.insert({matched_line,
					matched_column,
					line_number,
					column,
					depth_of_open});
		}
	};

	for(size_t i = 0; i < brackets_content.size(); i++){
		auto& line = brackets_content[i];
		for(size_t j = 0; j < line.size(); j++){
			if(!mask_valid[i][j]){
				continue;
			}
			auto c = line[j];
			if(c == '{'){
				process_open(i,j);
			}
			if(c == '}'){
				process_close(i,j);
			}
		}
	}
	return start_ends;
}

set<array<int,4>> FunctionBreakerC::find_start_end_of_brackets_of_given_depth(vector<string> brackets_content, int depth){
	set<array<int,4>> ret;
	set<array<int,5>> bracket_pairs = find_start_end_and_depth_of_brackets(brackets_content);
	for(auto [start_line,start_column,end_line,end_column,dep] : bracket_pairs){
		if(dep == depth){
			ret.insert({start_line,start_column,end_line,end_column});
		}
	}
	return ret;
}

int FunctionBreakerC::find_position_first_open_bracket(string s){
	for(size_t i = 0; i < s.size(); i++){
		char c = s[i];
		if(c == '{'){
			return i;
		}
	}
	return -1;
}

string FunctionBreakerC::extract_last_token_of_string(string s){
	vector<string> tokens;
	string cur_token = "";
	for(size_t i = 0; i < s.size(); i++){
		char c = s[i];
		if( Utils::is_empty_char(c) || Utils::is_special_char(c)){
			if(!cur_token.empty()){
				tokens.push_back(cur_token);
			}
			cur_token = "";
		}else{
			cur_token += c;
		}
	}
	if(!cur_token.empty()){
		tokens.push_back(cur_token);
	}

	if(tokens.empty()){
		return "";
	}
	return tokens.back();
}

Line_content FunctionBreakerC::build_line_code(int line_number, string content){
	Line_content ret;
	ret.line_number = line_number;
	ret.content = content;
	return ret;
}

vector<Line_content> FunctionBreakerC::get_lines_before_body_function(const vector<string> &file_content, int line_start_body_function, int pos_bracket){	
	vector<Line_content> ret;
	Line_content line_bracket = build_line_code(line_start_body_function,file_content[line_start_body_function]);
	//remove everything after {
	while(int(line_bracket.content.size()) > pos_bracket){
		line_bracket.content.pop_back();
	}
	ret.push_back(line_bracket);

	int until = max(0,line_start_body_function-NUMBER_OF_LINES_BEFORE_FOR_FUNCTION_NAME);
	for(int i = line_start_body_function-1; i >= until; i--){
		ret.push_back(build_line_code(i,file_content[i]));
	}
	reverse(ret.begin(),ret.end());

	//remove empty lines/empty characters at the end of lines
	while(!ret.empty()){
		if(ret.back().content.empty()){
			ret.pop_back();
			continue;
		}
		if(Utils::is_empty_char(ret.back().content.back())){
			ret.back().content.pop_back();
			continue;
		}
		break;
	}
	return ret;
}


vector<Line_content> FunctionBreakerC::remove_parenteses_at_the_end_of_the_scope(vector<Line_content> code){
	if(code.empty() || code.back().content.back() != ')'){
		return code;
	}
	int count_close_parenteses = 0;

	while(!code.empty()){
		string content = code.back().content;
		while(!content.empty()){
			if(content.back() == ')'){
				count_close_parenteses++;
			}
			if(content.back() == '('){
				count_close_parenteses--;
			}
			content.pop_back();
			if(count_close_parenteses == 0){
				break;
			}
		}
		code.back().content = content;
		if(count_close_parenteses == 0){
			break;
		}
		code.pop_back();
	}
	return code;
}

vector<Line_content> FunctionBreakerC::remove_content_until_find_parenteses_at_the_end(vector<Line_content> code){
	while(!code.empty()){
		string content = code.back().content;
		while(!content.empty()){
			if(content.back() == ')'){
				break;
			}else{
				content.pop_back();
			}
		}
		code.back().content = content;
		if(!content.empty()){
			break;
		}
		code.pop_back();
	}
	return code;
}

vector<Line_content> FunctionBreakerC::remove_parameters_of_declaration(vector<Line_content> code){
	if(!ALLOW_STRUCTS){
		auto ret = remove_content_until_find_parenteses_at_the_end(code);
		return remove_parenteses_at_the_end_of_the_scope(ret);
	}
	return remove_parenteses_at_the_end_of_the_scope(code);
}

pair<string,int> FunctionBreakerC::extract_function_name_and_line_from_declaration(const vector<string> &file_content, int line_start_body_function){
	int pos = find_position_first_open_bracket(file_content[line_start_body_function]);
	vector<Line_content> code_before_bracket = get_lines_before_body_function(file_content, line_start_body_function,pos);
	vector<Line_content> code = remove_parameters_of_declaration(code_before_bracket);
	if(code.empty()){
		return make_pair("",-1);
	}
	string ret = extract_last_token_of_string(code.back().content);
	return {ret,code.back().line_number};
}

vector<string> FunctionBreakerC::build_function_content(int start_number_line, int start_column, int end_number_line, int end_column, const vector<string> &file_content){
	vector<string> function_content;

	if(start_number_line == end_number_line){
		string line = "";
		for(int j = start_column; j <= end_column; j++){
			line += file_content[start_number_line][j];
		}
		function_content.push_back(line);
		return function_content;
	}

	string first_line = file_content[start_number_line];
	int first_line_size = first_line.size();
	string first_line_contribution = "";
	for(int j = start_column; j < first_line_size; j++){
		first_line_contribution += first_line[j];
	}
	function_content.push_back(first_line_contribution);

	for(int i = start_number_line+1; i < end_number_line; i++){
		function_content.push_back(file_content[i]);
	}

	string last_line = file_content[end_number_line];
	int last_line_size = last_line.size();
	string last_line_contribution = "";
	for(int j = 0; j <= end_column; j++){
		last_line_contribution += last_line[j];
	}
	function_content.push_back(last_line_contribution);

	return function_content;
}


bool FunctionBreakerC::is_body_function_empty(int start_number_line, int start_column, int end_number_line, int end_column,const vector<string> &file_content){
	vector<string> function_content = build_function_content(start_number_line, start_column, end_number_line, end_column, file_content);
	int count_not_empty_char = 0;
	for(auto line : function_content){
		for(auto c : line){
			if(!Utils::is_empty_char(c)){
				count_not_empty_char++;
			}
		}
	}
	bool is_empty = count_not_empty_char <= 2;
	return is_empty;
}

void FunctionBreakerC::process_function(int start_number_line, 
		int start_column,
		int end_number_line, 
		int end_column,
		string relative_path,
		const vector<string> &file_content){
	string first_line = file_content[start_number_line];
	auto [function_name,line_declaration] = extract_function_name_and_line_from_declaration(file_content,start_number_line);
	if(function_name.empty()){
		return;
	}
	if(IGNORE_EMPTY_FUNCTIONS){
		if(is_body_function_empty(start_number_line,start_column,end_number_line,end_column,file_content)){
			return;
		}
	}
	vector<string> function_content = build_function_content(start_number_line,start_column,end_number_line,end_column,file_content);

	create_source_file(start_number_line,end_number_line,relative_path,function_name,function_content);
	create_header_file(start_number_line,line_declaration,relative_path,function_name,file_content);
	create_info_file(line_declaration,start_number_line,end_number_line,relative_path,function_name);
}

string FunctionBreakerC::file_path_from_folder_path(string file_path, string folder_path){
	string ret = "";
	for(size_t i = folder_path.size(); i < file_path.size(); i++){
		ret += file_path[i];
	}
	return ret;
}

void FunctionBreakerC::file_breaker_c(string file_path, string folder_path){
	string relative_path = file_path_from_folder_path(file_path, folder_path);
	vector<string> file_content = Utils::read_file_generic(file_path);
	set<array<int,4>> start_end_of_functions = find_start_end_of_brackets_of_given_depth(file_content, C_RELEVANT_DEPTH);
	for(auto [start_line,start_column,end_line,end_column] : start_end_of_functions){
		process_function(start_line,start_column,end_line,end_column,relative_path,file_content);
	}
}

FunctionBreakerC::FunctionBreakerC(string file_path, string folder_path){
	file_breaker_c(file_path, folder_path);
}
