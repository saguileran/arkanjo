// Defines the preprocessor/setup step of the tool,
// where we do a heavy preprocessing of the input codebase
// to enable fast query response later.

#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <bits/stdc++.h> 
#include "parser.hpp"
#include "function_breaker.hpp"
using namespace std;

class Preprocessor{
	private:
		string PROJECT_PATH_MESSAGE = "Enter your project path:";
		string MINIMUM_SIMILARITY_MESSAGE = "Enter minimum similarity desired on using the tool:";
	public:
		void preprocess();
};

#endif
