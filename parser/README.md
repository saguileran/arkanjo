#Description

The output of [Duplicate Code Detection Tool](https://github.com/platisd/duplicate-code-detection-tool) is beautiful but a pain to retrive information on a workable manner. This script transform the output of the tool in a way more easy to handle

## How to Run

It is required a C++ compiler (Maybe standard Mac C++ compiler doesn't run because it does not has bits). You only need to Compile and run the code:

```
g++ parser.cpp -o parser
./parser $CAP < $INPUT_FROM_TOOL
```


The output start with a number n, the number of comparations made by the tool.

The following n lines of the output has two strings s,t and a decimal number SIMILARITY, a pair of files compared and  the similarity between them. 

The list of comparations of the output is sorted by similarity in decending order.

The $CAP is a optional parameter that filter the comparations that has similarity greater or equal to $CAP. By default $CAP=0, i.e, nothing is filtered.

The INPUT_FROM_TOOL was got simply by running the tool and redirecting the output to a file instead of the stdout with the use of the > on a linux terminal.
