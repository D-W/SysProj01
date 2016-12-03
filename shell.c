#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "executor.c"

int main() {

    //ask for user input
    printf("! ");
    char input[100];
    while(fgets(input, sizeof(input), stdin)) {

        //remove newline at end of entered commands
        char s[strlen(input)-1];
        strncpy(s, input, strlen(input)-1);

        //take string, split it into array of commands
        char ** arrCmd = parse_line(s, " ; ");

        //execute each command in order
        int i = 0;
        while (arrCmd[i]) {
            execute_command(arrCmd[i]);
        }

        printf("! ");
    }

    return 0;
}
