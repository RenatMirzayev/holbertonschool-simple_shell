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
        printf("#cisfun$ ");

        nread = getline(&line, &len, stdin);

        // Handle EOF (Ctrl+D)
        if (nread == -1)
        {
            free(line);
            exit(0);
        }

        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Check if the input is a single word (no spaces)
        if (strchr(line, ' ') != NULL) {
            fprintf(stderr, "./shell: Command must be a single word.\n");
            continue;
        }

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

