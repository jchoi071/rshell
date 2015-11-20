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
        vector<vector<char*> > vargs; //vector of arguments
        vector<Command*> commands; //vector of Command objects for easier command execution
        bool comment = false;
        bool connector = false;
        unsigned vargsIndex = 0;
        vargs.resize(1);
        while (arg != NULL && !comment) 
        {
            
            
            //command connector parsing
            
            if (arg[strlen(arg) - 1] == ';') 
            {   
                arg[strlen(arg) - 1] = 0;
                char* word = new char [strlen(arg) + 1];
                strcpy(word, arg);
                vargs.at(vargsIndex).push_back(word);       
                Command* c = new Command(vargs.at(vargsIndex), 0); //dynamically allocate memory for a new Command object
                commands.push_back(c); //put new object into Command vector
                ++vargsIndex;
                vargs.resize(vargsIndex + 1);
                connector = true;
                
                
            }       
            //the current argument is &&
            else if (strcmp(arg, "&&") == 0)
            {
                Command* c = new Command(vargs.at(vargsIndex), 1);
                commands.push_back(c);
                ++vargsIndex;
                vargs.resize(vargsIndex + 1);
                //connector = true;
                
            }
            //the current argument is ||
            else if (strcmp(arg, "||") == 0)
            {
                Command* c = new Command(vargs.at(vargsIndex), 2);
                commands.push_back(c);
                ++vargsIndex;
                vargs.resize(vargsIndex + 1);
                //connector = true;
            }
            //the current argument is #
            else if (arg[0] == '#')
            {
                Command* c = new Command(vargs.at(vargsIndex), 0);
                commands.push_back(c);
                ++vargsIndex;
                vargs.resize(vargsIndex + 1);
                comment = true;
                //connector = true;
            }
            //current argument is not a connector
            else
            {
                char* word = new char [strlen(arg) + 1];
                strcpy(word, arg);
                vargs.at(vargsIndex).push_back(word);
            }
            arg = strtok(NULL, " ");

            
        }
        //if there is no comment
        if (!comment)
        {
            //last command is created and placed in vector
            Command* c = new Command(vargs.at(vargsIndex), 0);
            commands.push_back(c);
        }
        //execute the first command in the vector
        bool status = commands.at(0)->executeCommand();
        int currentConnector = commands.at(0)->getConnector();
        
        //cout << currentConnector << endl;
        //if (!status) cout << "Fail" << endl; 
        //conditionally execute the rest of the commands
        for (unsigned d = 1; d < commands.size(); ++d)
        {
            //the connector was && and prev command was successful
            if (currentConnector == 1 && status)
            {
                status = commands.at(d)->executeCommand();
            }
            //the connector was || and prev command failed
            else if (currentConnector == 2 && !status)
            {
                status = commands.at(d)->executeCommand();
            }
            //the connector was ;
            else if (currentConnector == 0)
            {
                status = commands.at(d)-> executeCommand();
            }
            currentConnector = commands.at(d)->getConnector();              
        }
        /*
        for (unsigned a = 0; a < commands.size(); ++a)
        {
            commands.pop_back();
        }
        */
        
        //delete[] com;
        
    }
    else exit(0);
}

