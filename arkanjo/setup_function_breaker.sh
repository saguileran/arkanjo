#Compile
make breaker
g++ parser.cpp -o parser

#Read The project Directory which is desired to run the tool
echo "Enter your project path:"
read  path

echo "Enter minimum similarity desired on using the tool:"
read similarity

#Execute parser of the tool
rm -r tmp
./breaker $path

#Execute the tool and save in a temporary file
python3 -W ignore third-party/duplicate-code-detection-tool/duplicate_code_detection.py -d tmp/source > output_tool.txt
./parser $similarity < output_tool.txt > output_parsed.txt
