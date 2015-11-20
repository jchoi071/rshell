#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>

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

int exist(char* path, int flag)
{
    int status = 0;
    bool isDir = false;
    bool isFile = false;
    struct stat sb;
    status = stat(path, &sb);
    //cout << "Status: " << status << endl;
    if (status != 0)
    {
        perror ("File or directory does not exist");
        status = 1;
    }
    else
    {
        switch (sb.st_mode & S_IFMT)
        {
            case S_IFREG: 
                isFile = true;
                isDir = false;
                //cout << "S_IFREG" << endl; 
                break;
            case S_IFDIR: 
                isDir = true; 
                isFile = false;
                //cout << "S_IFDIR" << endl;
                break;
        }
        

        if (flag == 1 && !isFile) status = 1;
        else if (flag == 2 && !isDir) status = 1;
    }
    
    //cout << "Status: " << status << endl;
    
    return status;
}

int test(char* args[])
{
    //cout << "Entered test function" << endl;
    //flags: 0 = -e, 1 = -f, 2 = -d 
    int status = 0;   

    unsigned size = 0;
    while (args[size] != 0)
    {
        ++size;
        //cout << "Size " << size << endl;
    }
 
    //int size = strSize(args);
    if (strcmp(args[0], "[") == 0)
    {
        if (size == 3 && strcmp(args[2], "]") == 0) status = exist(args[1], 0);
        else if (size == 4 && strcmp(args[3], "]") == 0)
        {
            if (strcmp(args[1], "-e") == 0) status = exist(args[2], 0);
            else if (strcmp(args[1], "-f") == 0) status = exist(args[2], 1);
            else if (strcmp(args[1], "-d") == 0) status = exist(args[2], 2);
            else cout << "Invalid command usage" << endl;
        }
        else cout << "Invalid command usage" << endl;
    }

    else
    {
        if (size == 2) status = exist(args[1], 0);
        else if (size == 3)
        {
            if (strcmp(args[1], "-e") == 0) status = exist(args[2], 0);
            else if (strcmp(args[1], "-f") == 0) status = exist(args[2], 1);
            else if (strcmp(args[1], "-d") == 0) status = exist(args[2], 2);
            else cout << "Invalid command usage" << endl;
        }
        else cout << "Invalid command usage" << endl;

    }
    //else cout << "This shouldn't happen" << endl;
    
    //cout << "Status " << status << endl;
    return status;
}

int execute(char* args[])
{
    int result = 0;
    pid_t child;
    pid_t parent;
    int status = 0;

    child = fork();

    if (child < 0) //unsuccessful fork
    {
        perror("Error: Process wasn't forked.");
        result = 1;
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
            result = 1;
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
            result = 1;
            return result;
            exit(1);
        }
    }
    return result;
}
