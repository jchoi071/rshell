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
        ~Command();
        bool getPrevCommandStatus();
        vector<char*> getArgArray();
        int getConnector();
        void setPrevCommandStatus(bool status);
        bool executeCommand();
};

Command::Command(vector<char*> args, int connector)
{
    this->successful = true;
    this->args = args;
    this->connector = connector;    
}

/*Command::~Command()
{
    
    //args.erase(args.begin(), args.begin() + args.size());
    //args.clear();
}*/

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
    bool result = true;
    char** com = new char*[args.size()];
    for (unsigned a = 0; a < args.size(); ++a)
    {
        com[a] = args.at(a);
    }
    com[args.size()] = '\0';
    if (strcmp(com[0], "cd") == 0) result = cd(com);
    else result = execute(com);
    //delete[] com;
    return result;      
}   
#endif  
