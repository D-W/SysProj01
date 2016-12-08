#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "parse.h"
#include "executor.h"

/*====================void prompt()====================
Inputs:
Inputs nothing
Returns:
Returns nothing

Description:
1) Gets the username of the current user
2) Prints the username of the current user
=======================================================*/
void prompt() {
    char username[1024];
    getlogin_r(username, 1024);
    printf("%s$$$ ", username);
}

/*====================int main()====================
Inputs:
Inputs nothing
Returns:
Returns 0

Description:
1) Prints out a leading prompt
2) Begin an infinite while loop and await user input
3) Fgets user input into char input[]
4) Splits input around ';' into an array of strings of command arrCmd using parse_line(input, ';')
5) Execute each command in arrCmd in order using a while loop
6) Print the leading prompt once again before restarting the while loop
=======================================================*/
int main() {

    prompt();
    char input[100];
    while(1) {

        fgets(input, sizeof(input), stdin);
        //remove newline at end of entered commands
        input[strlen(input)-1] = '\0';

        //take string, split it into array of commands
        char ** arrCmd = parse_line(input, ';');

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
