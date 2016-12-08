#Systems Project 01 by Dylan Wright

Features:
    -Forks and executes commands
    -Parses multiple commands on one line
    -Redirects using > and <
Attempted:
    -Could not get pipes to work
Bugs:
    -Cannot directly make run, must make first then make run
    -Entering something that isn't a command causes the program to fork into a child process
    -Sometimes entering a command causes a segmentation fault
    -Entering an even number of commands on one line causes a segmentation fault

Files & Function Headers:

shell.c
    continuously runs the shell functions
    /*====================void prompt()====================
    Inputs:
    Inputs nothing
    Returns:
    Returns nothing

    Description:
    1) Gets the username of the current user
    2) Prints the username of the current user
    =======================================================*/

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

parse.c
    Handles all line parsing functions
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

executor.c
    Handles the forking and execution of commands
    /*====================void executeCommand()====================
    Inputs:
    char *s - A string of a singular command, which was created by strsep()-ing the inputted command line into an array of strings of separate commands by ';'
    Returns:
    Returns void

    Description:
    1) Takes the command string and splits it into an array of arguements
    2) Check if command contains '>' or '<'
        -If so, redirect command and arguments appropriately
    3) Checks if the command is "exit"
        -If the command is "exit" the parent program needs to exit instead of the forked child program
        -Therefore run exit(0) to exit the parent program.
    4) Checks if command is "cd"
        -If the command is "cd" the parent program needs to change directories instead of the forked child program
        -Therefore run chdir(arrArg[1]) to change the directory of the parent program to the next arguement in the command
        -If arrArg[1] does not exist change the directory to the home directory.
    5) If the command is neither "exit" nor "cd"
        a) Fork the command to a child process and run the command using execvp(arr[0], arr)
        b) Have the parent process wait until the child has completed the command before moving the next command in the command line
    ===============================================================*/

redirect.c
    Handles redirection using > and <
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
    
    /*====================void redirect()====================
    Inputs:
    char **input - An array of strings of arguments created by splitting the command string
    Returns:
    Returns void

    Description:
    1) Tries to find location of > and < in input
    2) If > is found
        -Redirect STDOUT to the file following '>'
    3) If < is found
        -Redirect STDIN to the file preceding '<'
    4) Fork and execute command using execvp
    =========================================================*/
