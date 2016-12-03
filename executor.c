#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "parse.c"

/*=======================void executeCommand()=======================
Inputs:
char * s - A string of a singular command, which was created by strsep-ing the inputted command line into separate commands by " ; "

Output:
Returns nothing

What Do?:
1) Takes the command string and splits it into an array of arguements
2) Checks if the command is "exit"
    If the command is "exit" the parent program needs to exit instead of the forked child program
    Therefore run exit(0) to exit the parent program
3) Checks if command is "cd"
    If the command is "cd" the parent program needs to change directories instead of the forked child program
    Therefore run chdir(arrArg[1]) to change the directory of the parent program to the next arguement in the command
4) If the command is neither "exit" nor "cd"
    a) Fork the command to a child process and run the command using execvp(arr[0], arr)
    b) Have the parent process wait until the child has completed the command before moving the next command in the command line
===================================================================*/
void execute_command(char * s) {

    //take string, split it into array of arguements
    char ** arrArg = parse_line(s, " ");

    //check if command is "exit", if so, exit(0)
    if (strcmp(arrArg[0], "exit") == 0) {
        exit(0);
    }

    //check if command is "cd", if so, chdir(arrArg[1]);
    else if (strcmp(arrArg[0], "cd") == 0) {
        if (arrArg[1]) {
            chdir(arrArg[1]);
        }
        else {
            chdir(getenv("HOME"));
        }
    }
    else {
        int f = fork();
        int status;
        //if the process is a child, run the command
        if (f == 0) {
            execvp(arrArg[0], arrArg);
        }
        //if the process is a parent, wait until the child process finishes running
        else {
            wait(&status);
        }
    }
}
