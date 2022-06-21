#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE_OF_COMMAND 512
char command[MAX_SIZE_OF_COMMAND];

char *inbuilt_commands[] = {
    "cd",
    "ls",
    "pwd",
};

int main() 
{
    while (1)
    {
        printf("\033[0;32m");
        printf("this is the prompt message-> ");
        printf("\033[0m");
        scanf("\n");
        scanf("%[^\n]s", command);
        if (!strcmp(command,"exit"))
        {
            exit(1);
        }
        printf("%s\n", command);
    }
    
}