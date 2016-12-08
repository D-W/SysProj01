#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "parse.h"

/*====================char * trim()====================
Inputs:
char *line - A string of either a single command with its arguments, or of multiple commands with their arguments entered by the user
Returns:
char *str - A string containing the same information as the inputted line, without any leading or trailing spaces

Description:
1) Allocates memory to new string str and copies over line into str to create a mutable string
2) Trims off leading spaces of str using a while loop
3) Trims off trailing spaces of str using a while loop and inserting a terminating 0
4) Returns the modified string str
=======================================================*/
char * trim(char *line) {
    //allocate memory to create mutable string
    char *str = (char *)malloc(100);
    strcpy(str, line);
    //trim off leading spaces
    while(str[0] == ' ') {
        str++;
    }
    //trim off trailing ' '
    int i = strlen(str)-1;
    while(str[i] == ' ') {
        i--;
    }
    str[i+1] = '\0';
    return str;
}

/*====================int count_tokens()====================
Inputs:
char *line - A string of either a single command with its arguments, or of multiple commands with their arguments entered by the user, with any leading or trailing spaces removed by trim()
char delim - A character that line will be separated around
Returns:
int tokens - An int representing the number of tokens contained in line separated by delim

Description:
1) Sets the initial value of tokens to 1, as any input will always be at least 1 token
2) Traverses through string line using a while loop and searching for any occurrences of char delim
    -If an occurrence of delim is found within line increase tokens by one
3) Returns final token count tokens
============================================================*/
int count_tokens(char *line, char delim) {
    //tokens must at least be equal to 1
    int tokens = 1;
    //traverse through line
    int i = 0;
    while (i < strlen(line)) {
        if ((line[i] - delim) == 0) {
            tokens++;
        }
        i++;
    }
    //return token count
    return tokens;
}

/*====================char **parse_line()====================
Inputs:
char *line - A string of either a single command with its arguments, or of multiple commands with their arguments entered by the user
char delim - A character that line will be separated around
Returns:
char **arr - An array of strings containing the values of line divided into separate commands and arguments around delim

Description:
1) Creates a new string s which is the char * creating by trim()-ing line
2) Allocates memory to a new array of strings arr based off of how many tokens are in s
3) Splits s into arr around delim through strsep()-ing s around delim
4) Returns newly created array arr
============================================================*/
char ** parse_line(char * line, char delim) {
    //remove leading and trailing zeros
    char *s = trim(line);
    //allocate an appropriate amount of memory to create a mutable array
    char **arr = (char **)malloc(((sizeof(char *)) * (count_tokens(s, delim))));
    //split the array around delim
    char *str = s;
    char *arg;
    int i = 0;
    while ((arg = strsep(&str, &delim)) != NULL) {
        arr[i] = arg;
        i++;
    }
    //return array of commands and their arguements
    return arr;
}
