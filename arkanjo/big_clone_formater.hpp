#include <bits/stdc++.h> 

#include "path.hpp"
#include "function.hpp"
#include "similarity_table.hpp"

using namespace std;

//This class expects to be executed in the contest of the folders of the BigCloneBench dataset 
class Big_Clone_Formater{

	string format_relative_path(string relative_path);
	string build_path_formated_string(Path path);
	auto process_similar_path_pair(Path path1, Path path2, double similarity);
	public:
	Big_Clone_Formater(Similarity_Table *similarity_table);
};
