#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_SIZE_OF_COMMAND 512
char command[MAX_SIZE_OF_COMMAND];

int main() 
{
    while (1)
    {
        printf("this is the prompt message-> ");
        // scanf("\n");
        // scanf("%[^\n]s", command);
        fgets(command, MAX_SIZE_OF_COMMAND,stdin); 
        if (!strcmp(command,"exit"))
        {
            exit(1);
        }
        
        printf("%s", command);
    }
    
}