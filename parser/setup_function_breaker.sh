#Download Tool from Github
rm  -r duplicate-code-detection-tool
git clone https://github.com/platisd/duplicate-code-detection-tool.git

echo "Do you wish to install Tool dependencies?(Y/N)" 
read install

if [[ $install == "Y" ]]; then 
	sudo apt install python3-nltk
	sudo apt install python3-gensim
	sudo apt install python3-astor
	sudo python3 -m nltk.downloader punkt
fi

#Compile
g++ function_breaker.cpp -o function_breaker

#Read The project Directory which is desired to run the tool
echo "Enter your project path:"
read  path

echo "Enter minimum similarity desired on using the tool:"
read similarity

#Execute parser of the tool
sudo rm -r tmp
./function_breaker $path

#Execute the tool and save in a temporary file
sudo python3 -W ignore duplicate-code-detection-tool/duplicate_code_detection.py -d tmp/source > output_tool.txt
./parser $similarity < output_tool.txt > output_parsed.txt
