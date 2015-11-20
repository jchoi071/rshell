#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string.h>
#include "execute.h"

using namespace std;

class Command
{   
    private:
        bool successful;
        vector<char*> args;
        //; = 0, && = 1, || = 2)
        int connector;
    public:
        Command (vector<char*> args, int connector);
        //~Command();
        bool getPrevCommandStatus();
        vector<char*> getArgArray();
        int getConnector();
        void setPrevCommandStatus(bool status);
        bool executeCommand();
};

Command::Command(vector<char*> args, int connector)
{
    this->successful = true;
    for (unsigned a = 0; a < args.size(); ++a)
    {
        this->args.push_back(args.at(a));
    }
    //this->args = args;
    this->connector = connector;    
}

/*
Command::~Command()
{
    
    for (unsigned a = 0; a < args.size(); ++a)
    {
        delete args.at(a);
    }
}
*/

bool Command::getPrevCommandStatus()
{
    return successful;
}

vector<char*> Command::getArgArray()
{
    return args;
}

int Command::getConnector()
{
    return connector;
}

void Command::setPrevCommandStatus(bool status)
{
    successful = status;
}

bool Command::executeCommand()
{
    int result = 1;
    char** com = new char* [args.size() + 1];
    for (unsigned a = 0; a < args.size(); ++a)
    {
        com[a] = new char[strlen(args.at(a)) + 1];
        strcpy(com[a], args.at(a));
    }
    
    com[args.size()] = 0;
    //com[args.size()] = '\0';
    if (strcmp(com[0], "cd") == 0) result = cd(com);
    else if (strcmp(com[0], "test") == 0 || strcmp(com[0], "[") == 0) result = test(com);
    else result = execute(com);
    //delete[] com;
    
    bool r = false;
    if (result == 0) r = true;
    
    //if (!r) cout << "FAIL" << endl;
    
    return r;      
}   
#endif  
