#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child_pid;
    int status;

    for (int i = 0; i < 5; i++)
    {
        child_pid = fork();

        if (child_pid == -1) 
        {
            perror("Error during fork");
            return 1;
        }

        if (child_pid == 0) 
        {
            char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
            printf("Child %d: Executing ls -l /tmp\n", i + 1);

            if (execve(argv[0], argv, NULL) == -1)
            {
                perror("Error during execve");
                return 1;
            }
        }
        else
        {
            
            wait(&status);
            printf("Parent: Child %d has finished execution\n", i + 1);
        }
    }

    return 0;
}

