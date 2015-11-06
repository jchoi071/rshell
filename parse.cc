#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "Command.h"

using namespace std;

void parse(string console)
{
	//cout << console << endl;
	//bool result = true;
	if (console != "exit")
	{
		char* com = new char [console.length() + 1]; //allocate memory to cstring com
		strcpy (com, console.c_str()); //convert string console to cstring and set cstring com to it
		char* arg = strtok(com, " "); //first strtok
		vector<char*> vargs; //vector of arguments
		vector<Command*> commands; //vector of Command objects for easier command execution
		bool comment = false;
		while (arg != NULL && !comment) 
		{
			//command connector parsing
			
			if (arg[strlen(arg) - 1] == ';') 
			{	
				arg[strlen(arg) - 1] = '\0';
				vargs.push_back(arg);		
				Command* c = new Command(vargs, 0); //dynamically allocate memory for a new Command object
				commands.push_back(c); //put new object into Command vector
				vargs.clear(); //wipe the vargs vector so that the next set of arguments can be inserted
				
			}		

			else if (strcmp(arg, "&&") == 0)
			{
				Command* c = new Command(vargs, 1);
				commands.push_back(c);
				vargs.clear();
				
			}

			else if (strcmp(arg, "||") == 0)
			{
				Command* c = new Command(vargs, 2);
				commands.push_back(c);
				vargs.clear();
				
			}
	
			else if (arg[0] == '#')
			{
				Command* c = new Command(vargs, 0);
				commands.push_back(c);
				vargs.clear();
				comment = true;
			}
			//current argument is not a connector
			else vargs.push_back(arg);
			arg = strtok(NULL, " ");

			
		}
		if (!comment)
		{
			//last command is created and placed in vector
			Command* c = new Command(vargs, 0);
			commands.push_back(c);
		}
		//execute every command in the vector
		bool status = commands.at(0)->executeCommand();
		int currentConnector = commands.at(0)->getConnector();
		for (unsigned d = 1; d < commands.size(); ++d)
		{
			if (currentConnector == 1 && status)
			{
				status = commands.at(d)->executeCommand();
			}
			else if (currentConnector == 2 && !(status))
			{
				status = commands.at(d)->executeCommand();
			}
			else if (currentConnector == 0)
			{
				status = commands.at(d)-> executeCommand();
			}
			currentConnector = commands.at(d)->getConnector();				
		}
		
		
		//commands.erase(commands.begin(), commands.begin() + commands.size());
		//commands.clear();
		
		delete[] com;
		
	}
	else exit(0);
}

