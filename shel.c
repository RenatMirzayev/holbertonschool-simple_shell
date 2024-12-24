#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;

    while (1)
    {
        // Only print the prompt if stdin is a terminal (interactive mode)
        if (isatty(fileno(stdin))) {
            printf("#cisfun$ ");
        }

        nread = getline(&line, &len, stdin);

        // Handle EOF (Ctrl+D)
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        pid = fork();

        if (pid == 0)
        {
            // Execute the command
            if (execlp(line, line, NULL) == -1) {
                perror("./shell");
                exit(1);
            }
        }
        else if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }

    free(line);
    return 0;
}

