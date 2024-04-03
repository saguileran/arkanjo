g++ parser.cpp -o parser
g++ filter.cpp -o filter

ARGC=$#

if [[ $ARGC -eq 0 ]]; then

	echo "bash run.sh similar FILE_NAME MIN_SIMILARITY-->"
	echo "		find files that the similarity to a given file is greater or equal to a given value MIN"
	echo ""
	echo "bash run.sh all MIN_SIMILARITY --> "
	echo "		finds the quantity and all pair of files that the similarity is greater or equal to a given value"
	echo ""
	echo "On both commands, similarity is a number between 0 and 100"

	exit
fi

option=$1
shift

if [[ $option == "similar" ]]; then
	
	if [ $ARGC -le 2 ]; then
		echo "not enough parameters"
		exit
	fi

	file_name=$1
	shift
	similarity=$1

	./parser $similarity < output_tool.txt > tmp.txt
	./filter $file_name < tmp.txt 
	rm tmp.txt
	exit
fi

if [[ $option == "all" ]]; then

	if [ $ARGC -le 1 ]; then
		echo "not enough parameters"
		exit
	fi
	
	similarity=$1
	./parser $similarity < output_tool.txt
	
	exit
fi


echo "bash run.sh similar FILE_NAME MIN_SIMILARITY-->"
echo "		find files that the similarity to a given file is greater or equal to a given value MIN"
echo ""
echo "bash run.sh all MIN_SIMILARITY --> "
echo "		finds the quantity and all pair of files that the similarity is greater or equal to a given value"
echo ""
echo "On both commands, similarity is a number between 0 and 100"
