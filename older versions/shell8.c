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
    int i = 0;
    char *split = " & ";
    scanf("\n");
    scanf("%[^\n]s", command);
    separate_commands[i] = strtok(command, "&");
    while (separate_commands[i] != NULL)
    {
        printf("%s\n", separate_commands[i]);
        i++;
        separate_commands[i] = strtok(NULL, "&");
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
        // exit if command is "exit"
        if (!strcmp(command,"exit"))
        {
            exit(1);
        }
        // printf("%s\n", separate_commands[0]);
    }
    
}