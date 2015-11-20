all:
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic src/Command.h src/execute.h src/parse.cc src/main.cc -o bin/rshell

rshell: 
	mkdir -p bin
	g++ -Wall -Werror -ansi -pedantic src/Command.h src/execute.h src/parse.cc src/main.cc -o bin/rshell 
