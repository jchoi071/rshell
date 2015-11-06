#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cerrno>

using namespace std;

bool cd(char* args[])
{
    int status = 0;
    bool result = true;
    status = chdir(args[1]);
    if (status != 0)
    {
        perror ("cd Fail");
        result = false;
        return result;
        exit(1);
    }
    return result;
}

bool execute(char* args[])
{
    bool result = true;
    pid_t child;
    pid_t parent;
    int status = 0;

    child = fork();

    if (child < 0) //unsuccessful fork
    {
        perror("Error: Process wasn't forked.");
        result = false;
        return result;
        exit(1);    
    }
    else if (child == 0) //successful fork
    {
        //execvp(args[0], args);
        //perror("Fail");
        
        status = execvp(args[0], args);
        //cout << status << ' ' << errno << endl;
        if (status != 0)
        {
            perror("Fail");
            //status = errno;
            result = false;
            return result;
            exit(1);
        }
        else exit(0);
    }
    else if (child > 0) 
    {
        //if () result = false;
        if((parent = wait(&status)) < 0)
        {
            perror("Waiting");
            result = false;
            return result;
            exit(1);
        }
    }
    return result;
}
