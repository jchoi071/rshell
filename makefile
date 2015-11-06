all:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic Command.h execute.h parse.cc main.cc -o bin/rshell

rshell: 
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic Command.h execute.h parse.cc main.cc -o bin/rshell 
