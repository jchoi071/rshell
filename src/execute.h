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


bool cd(char* args[]) //function for executing cd
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

int exist(char* path, int flag) //helper function to determine existence of files/directories
{
    int status = 0;
    bool isDir = false;
    bool isFile = false;
    struct stat sb;
    status = stat(path, &sb); //status system call
    //cout << "Status: " << status << endl;
    if (status != 0) //if file or directory does not exist
    {
        perror ("File or directory does not exist");
        status = 1;
    }
    else //if file or directory does exist
    {
        switch (sb.st_mode & S_IFMT)
        {
            case S_IFREG: //if path is file
                isFile = true;
                isDir = false;
                //cout << "S_IFREG" << endl; 
                break;
            case S_IFDIR: //if path is directory
                isDir = true; 
                isFile = false;
                //cout << "S_IFDIR" << endl;
                break;
        }
        

        if (flag == 1 && !isFile) status = 1; //if -f used but path is not a file
        else if (flag == 2 && !isDir) status = 1; //if -d used but path is not a directory
        
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
    while (args[size] != 0) //find size of args array
    {
        ++size;
        //cout << "Size " << size << endl;
    }
 
    //int size = strSize(args);
    if (strcmp(args[0], "[") == 0) //if [] is used
    {
        if (size == 3 && strcmp(args[2], "]") == 0) status = exist(args[1], 0); //if -e is not used
        else if (size == 4 && strcmp(args[3], "]") == 0) //if any flag is used
        {
            if (strcmp(args[1], "-e") == 0) status = exist(args[2], 0); //-e
            else if (strcmp(args[1], "-f") == 0) status = exist(args[2], 1); //-f
            else if (strcmp(args[1], "-d") == 0) status = exist(args[2], 2); //-d
            else cout << "Invalid command usage" << endl; //if invalid flag is used
        }
        else cout << "Invalid command usage" << endl; //if ending ']' is not present
    }

    else //if normal test is used
    {
        if (size == 2) status = exist(args[1], 0); //if -e is not used
        else if (size == 3) //if any flag is used
        {
            if (strcmp(args[1], "-e") == 0) status = exist(args[2], 0); //-e
            else if (strcmp(args[1], "-f") == 0) status = exist(args[2], 1); //-f
            else if (strcmp(args[1], "-d") == 0) status = exist(args[2], 2); //-d
            else cout << "Invalid command usage" << endl; //if invalid flag is used
        }
        else cout << "Invalid command usage" << endl; //if command contains extra parameters

    }
    //else cout << "This shouldn't happen" << endl;
    
    //cout << "Status " << status << endl;
    return status;
}

int execute(char* args[]) //function for executing commands based in programs
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
