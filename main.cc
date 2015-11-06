#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

void parse(string console);

int main()
{	
	bool run = true;
	while (run)
	{
		cout << "$ ";
		string console;
		getline(cin, console);
		parse(console);
		if (console == "exit")
		{
			//cout << console << endl;
			run = false;
			exit(0);
			break;
		}
		//else parse(console);
		
	}
	return 0;
}
