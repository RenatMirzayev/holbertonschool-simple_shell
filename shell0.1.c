#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

extern char **environ; // Declare environ

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[2]; // Array to hold the command and NULL terminator
    pid_t pid;
    int status;
    char *prompt = "#cisfun$ ";

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("%s", prompt); // Display prompt if running interactively

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            if (isatty(STDIN_FILENO))
                 printf("\n");
            break; // Handle EOF (Ctrl+D)
        }

        // Remove trailing newline
        command[strcspn(command, "\n")] = '\0';

        // Split into command and arguments (only command in this version)
        args[0] = command;
        args[1] = NULL;

        if (args[0][0] == '\0') {
            continue;
        }
       
        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
             // Child process
            if (execve(args[0], args, environ) == -1)
            {
                perror("./shell"); // Print custom error message
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            if (waitpid(pid, &status, 0) == -1) {
                 perror("waitpid");
                 exit(EXIT_FAILURE);
            }
        }

    }

    return (EXIT_SUCCESS);
}
