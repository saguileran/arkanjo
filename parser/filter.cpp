/*
This file expect the output of parser.cpp
This code filter the output only printing the files similar to files that contains a given pattern passed as argc
The code filter every file that has the pattern as a substring, so be carefull with duplications
*/

#include <bits/stdc++.h> 
using namespace std;


bool matches(string text, string pattern){
	return text.find(pattern) != string::npos;
}

void filter(string file_name){
	int number_comparations;
	cin >> number_comparations;

	set<pair<string,double>> similar_files;
	
	for(int i = 0; i < number_comparations; i++){
		vector<string> files_compared(2);
		double similarity;

		cin >> files_compared[0] >> files_compared[1];
		cin >> similarity;
		
		for(int j = 0; j < 2; j++){
			string file1 = files_compared[j];
			string file2 = files_compared[j^1];
			
			if(matches(file1,file_name)){
				similar_files.insert(make_pair(file2,similarity));
			}
		}
	}

	for(auto [similar_file,similarity] : similar_files){
		cout << similar_file << ' ';
		cout << fixed << setprecision(2) << similarity << endl;
	}
}



int main(int argc, char *argv[]){
	if(argc <= 1){
		cout << "Erro: Expect the name of the file to be filtred, but none has given" << endl;
		return 0;
	}
	string pattern(argv[1]);
	filter(pattern);
	return 0;
}
