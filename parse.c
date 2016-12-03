#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
char * trim(char *line) {

}
*/

int count_tokens(char * line, char * delim) {
    //tokens must at least be equal to 1
    int tokens = 1;
    //find the length of the delim
    int delim_len = strlen(delim);
    //while we can still find an occurance of delim in line
    while ((line = strstr(line,delim))) {
        //increase the position in memory of line by the length of delim
        line += delim_len;
        //increase the count of tokens
        tokens++;
    }
    //return token count
    return tokens;
}

/*
char ** parse_line(char * line, char * delim) {
    char ** arr = (char **)malloc(1000);
    printf("test");
    char * str = line;
    char * arg;
    int i = 0;
    while ((arg = strsep(&str, delim)) != NULL) {
        arr[i] = arg;
        i++;
    }
    return arr;
}
*/


char ** parse_line(char * line, char * delim) {
    char * arr[count_tokens(line, delim)];
    char * str = line;
    char * arg;
    int i = 0;
    while ((arg = strsep(&str, delim)) != NULL) {
        arr[i] = arg;
        i++;
    }
    char ** ans = arr;
    return ans;
}
