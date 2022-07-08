#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h> 

static char* currentDirectory;

// setting max input buffer
#define MAX_SIZE_OF_COMMAND 512
char command[MAX_SIZE_OF_COMMAND];
char *separate_commands[MAX_SIZE_OF_COMMAND];
char *int_cmd[MAX_SIZE_OF_COMMAND];
int total_commands = 0;

void welcome()
{
    printf("\n\nwelcome %s\n", getenv("USER"));
    printf("\n\n\t-----------------------------------------\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|--------------Linux Shell--------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|--------------Pawan Bajaj--------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t|---------------------------------------|\n");
    printf("\t-----------------------------------------\n\n\n");
    printf("use \"exit\" to quit and \"help\" for info\n\n\n");

}

void info()
{
    printf("\nthis is a linux shell made by Pawan Bajaj\n\ncurrently working commands: cd, help, touch, ls, rm\n\nfor contact, email: pawanbaja2012@gmail.com\n\n:)\n\n");
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

void int_cmdd()
{
    int i = 0;
    int_cmd[i] = strtok(separate_commands[total_commands], " ");
    while (int_cmd[i] != NULL)
    {
        // printf("%s\n", separate_commands[total_commands]);
        i++;
        int_cmd[i] = strtok(NULL, " ");
    } 

}

void input()
{
    scanf("\n");
    scanf("%[^\n]s", command);
    separate_commands[total_commands] = strtok(command, "&");
    int_cmdd();
    while (separate_commands[total_commands] != NULL)
    {
        // printf("%s\n", separate_commands[total_commands]);
        total_commands++;
        separate_commands[total_commands] = strtok(NULL, "&");

    }   
}

void parse()
{
    int i = 0;
    while (int_cmd[i] != NULL)
    {
        if (strcmp(int_cmd[i], "cd") == 0)
        {
            if (int_cmd[1] != NULL)
            {
                // if ".." used with cd, go back to previous directory
                if (!strcmp(int_cmd[1], ".."))
                {
                    chdir(getenv("OLDPWD"));
                }
                // change directory
                else
                    chdir(int_cmd[1]);
            }
            // if only cd is the command, go back to home directory
            else
                chdir(getenv("HOME"));
            break;
            
        }
        // for basic info
        else if (strcmp(int_cmd[i], "help") == 0)
        {
            info();
        }
        // exit if command is "exit"
        else if (!strcmp(int_cmd[i],"exit"))
        {
            exit(1);
        }
        // list of directories
        else if (!strcmp(int_cmd[i], "ls")) 
        {
            DIR *d;
            struct dirent *dir;
            d = opendir(getcwd(currentDirectory,1024));
            if (d)
            {
                while ((dir = readdir(d)) != NULL) {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }
        // creating a new file 
        else if (!strcmp(int_cmd[i], "touch")) 
        {
            FILE *f1;
            f1 = fopen(int_cmd[1], "w");
            return;
        }
        else if (!strcmp(int_cmd[i], "rm")) 
        {
            // if file gets deleted
            if(!remove(int_cmd[1]))
            {
                printf("%s deleted successfully\n", int_cmd[1]);
            }
            // if the file does not exist
            else {
                printf("\033[0;33m");
                printf("file {%s} doesn't exist\n", int_cmd[1]);
                printf("\033[0m");
            }
            return;
        }
        // for invalid commands
        else {
            printf("\033[0;33m");
            printf("command invalid {%s}\n", int_cmd[i]);
            printf("\033[0m");
        }
        i++;
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