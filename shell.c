#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static char* currentDirectory;

// setting max input buffer
#define MAX_SIZE_OF_COMMAND 512
char command[MAX_SIZE_OF_COMMAND];
char *separate_commands[MAX_SIZE_OF_COMMAND];
int total_commands = 0;

void welcome()
{
    printf("\n\n\t-----------------------------------------\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|--------------Linux Shell--------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|--------------Pawan Bajaj--------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t-----------------------------------------\n\n\n");

}

void info()
{
    printf("\nthis is a linux shell made by Pawan Bajaj\n\ncurrently working commands: cd, help\n\nfor contact, email: pawanbaja2012@gmail.com\n\n:)\n\n");
}

void shellPrompt(){
	// We print the prompt in the form "<user>@<host> <cwd> >"
	char hostn[1204] = "";
	gethostname(hostn, sizeof(hostn));
    // changing the color for prompt message
    printf("\033[0;32m");
	printf("%s@%s %s > ", getenv("USER"), hostn, getcwd(currentDirectory, 1024));
    printf("\033[0m");
}

void input()
{
    
    char *split = " & ";
    scanf("\n");
    scanf("%[^\n]s", command);
    separate_commands[total_commands] = strtok(command, "&");
    while (separate_commands[total_commands] != NULL)
    {
        // printf("%s\n", separate_commands[total_commands]);
        total_commands++;
        separate_commands[total_commands] = strtok(NULL, "&");
    }   
}

void parse()
{
    // cd returns to the home directory
    if (strcmp(separate_commands[0], "cd") == 0)
    {
        chdir(getenv("HOME"));
    }
    // for basic info
    else if (strcmp(separate_commands[0], "help") == 0)
    {
        info();
    }
    // exit if command is "exit"
    else if (!strcmp(separate_commands[0],"exit"))
    {
        exit(1);
    }
    // for invalid commands
    else {
        printf("\033[0;33m");
        printf("command invalid {%s}\n", separate_commands[0]);
        printf("\033[0m");
    }

    
}

int main(int argc, char const *argv[], char **environ)
{
    welcome();
    while (1)
    {
        // setting environment variable for the child
        setenv("shell",getcwd(currentDirectory, 1024),1);
        
        // setting the entire buffer to NULL
        memset(command, '\0', MAX_SIZE_OF_COMMAND);

        shellPrompt();
        input();
        parse();
        // exit if command is "exit"
        
        // printf("%s\n", separate_commands[0]);
    }
    
}