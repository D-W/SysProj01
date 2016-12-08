#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*====================void redirect()====================
Inputs:
char **arr - An array of strings of arguments created by splitting the command string
Returns:
int i - An int representing the location of target in arr, -1 if target not found

Description:
1) Uses a while loop to try and find target in arr
    a) If target is found, return location in arr i
    b) If target cannot be found, return -1
=========================================================*/
int find(char **arr, char *target) {
	int i = 0;
	while(arr[i]){
		if(!strcmp(arr[i], target)) {
			return i;
		}
		i++;
	}
	return -1;
}

/*====================void redirect()====================
Inputs:
char **arr - An array of strings of arguments created by splitting the command string
Returns:
Returns void

Description:
1) Tries to find location of > and < in arr
2) If > is found
    -Redirect STDOUT to the file following '>'
3) If < is found
    -Redirect STDIN to the file preceding '<'
4) Fork and execute command using execvp
=========================================================*/
void redirect(char **arr) {
    /*prepare to hold:
     locations of > and < in input,
     the string of the desired file name if > or < found,
     and value of file descriptor if > or < found
     */
    int redir_stdout;
    int redir_stdin;
    char *fn;
    int fd;
    //try to find location of > and < in input
    redir_stdout = find(arr, ">");
    redir_stdin = find(arr, "<");
    //if > is found
    if (redir_stdout != -1) {
        fn = arr[redir_stdout+1];
        fd = open(fn, O_CREAT | O_WRONLY, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        arr[redir_stdout] = 0;
    }
    //if < is found
    else if (redir_stdin != -1) {
        fn = arr[redir_stdin+1];
        fd = open(fn, O_CREAT | O_RDONLY, 0644);
        dup2(STDIN_FILENO, fd);
        close(fd);
        arr[0] = arr[redir_stdin];
    }
    //fork and execute command
    int f = fork();
    if(!f) {
        execvp(arr[0], arr);
    }
    else {
        int status;
        wait(&status);
    }
}
