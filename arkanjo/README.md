# Description

This tool uses as a subrotine the tool from [Duplicate Code Detection Tool](https://github.com/platisd/duplicate-code-detection-tool)  as a subrotine to compare functions


The tool was created with the desire to facilitate code duplication detection and at the moment the tool it has the following functionalities:

- Compare every pair of functions and structs of C code on a folder and return every pair that pass a threhold of similarity.

- Given a function/struct name, return every function/struct that the similarity with the function/struct given pass a threhold of similarity.

The concept of similarity is a black-box concept given by the [Duplicate Code Detection Tool](https://github.com/platisd/duplicate-code-detection-tool) with the help of Machine Learning.

Similarity of two objects is a number between on 0 and 100. Higher the number, higher the similarity between the objects.

## Requirements

It is required access to internet to download the subrotine tool.

It is required the g++. The standard C++ compiler in the GNU/Linux environment

## TODO 

It is required to install the libjsoncpp-dev package with apt-get or anything like that. Maybe this tool only works in ubuntu because of how I read Json files. I will look into that latter. Also remember to add -ljsoncpp flag latter.

Remember to install : sudo apt-get install libjsoncpp-dev 

Features I want to do:

- Count number of lines affected by code duplication in the repository. Create a kind of report ?

- Given n files, remove the common function in them and create a temporary file .c and .h that has the common functions. In this feature the user should be able to select which functions to remove and it would be nice to have something to visualize the functions and the diff between files.

- Given a function, list the other functions that are similar to this one.

- Given a file, to every function in this file that is a duplicate function, give the user the option to list which files use this function.

- Did I thought In more? I do not know. In order of difficult to implement is second, first, fourth, third feature. 


## How to Setup

Execute the setup_function_breaker.sh and follow the steps:

```
sudo bash setup_function_breaker.sh
```

After you done the setup, you can request comparations about the folder you given to the tool while you run the setup script.

It is not stored setup's. So if you want to check another code base you will lose the setup of a previous one.

## How to Run

If you has done the standard setup. This is the following command you can execute with the tool: 


### find functions that the similarity to a given function is greater or equal to a given value MIN


```
sudo bash run.sh similar FUNCTION_NAME MIN_SIMILARITY
```

### finds the quantity and all pair of functions that the similarity is greater or equal to a given value:

```
sudo bash run.sh all MIN_SIMILARITY
```

The output of the all command  start with a number n, the number of comparations made by the tool.

The following n lines of the output has two strings s,t and a decimal number SIMILARITY, a pair of functions compared and  the similarity between them. 

The list of comparations of the output is sorted by similarity in decending order.

### Find files that the similarity to a given file from the output of the all command:
```
sudo bash run.sh similar_from_all FILE_NAME OUTPUT_ALL
```

To execute the similar_from_all, save the output of an all command on a temporary file and pass the name of the file to the command.
