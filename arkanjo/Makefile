make: 
	g++ utils.cpp path.cpp similarity_table.cpp similar_function_finder.cpp counter/counter_duplication_code_trie.cpp counter/counter_duplication_code.cpp similarity_explorer.cpp big_clone/big_clone_formater.cpp function.cpp big_clone/big_clone_tailor_evaluator.cpp random_selector.cpp orchestrator.cpp -o exec -ljsoncpp -g

breaker:
	g++ utils.cpp pre/function_breaker.cpp -o breaker -ljsoncpp -g

preprocessor:
	g++ pre/parser.cpp pre/preprocessor.cpp pre/preprocessor_main.cpp -o preprocessor -g
