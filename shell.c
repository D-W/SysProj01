#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "executor.c"


void prompt(){
    char username[1024];
    getlogin_r(username, 1024);
    char hostname[1024];
    gethostname(hostname,1024);
    char cwd[1024];
    getcwd(cwd,1024);
    printf("%s:%s %s$ ", hostname, cwd, username);
}

int main() {

    prompt();
    char input[100];
    while(1) {

        fgets(input, sizeof(input), stdin);
        //remove newline at end of entered commands
        input[strlen(input)-1] = '\0';

        //take string, split it into array of commands
        char ** arrCmd = parse_line(input, " ; ");

        //execute each command in order
        int i = 0;
        while (arrCmd[i]) {
            execute_command(arrCmd[i]);
            i++;
        }

        prompt();
    }

    return 0;
}
